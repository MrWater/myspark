#include <libaio.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <sys/eventfd.h>
#include <time.h>
#include <sys/fcntl.h>
#include <aio.h>
#include <map>

#define CONN_N 10240
#define EPEVNET_N 1024
#define BUF_SIZE 1024

std::map<int, char*> socket_bufs;

void Add_Event(int epfd, int socket, int events);
void Mod_Event(int epfd, int socket, int events);
void InitServer(int listen_socket);
void AcceptConn(int epfd, int listen_socket);
void HandleFinishAio(int epfd, int efd, io_context_t ctx, io_event *events);
void SubmitWrite(io_context_t ctx, int fd, int efd, char*buf, int len);
void SubmitRead(io_context_t ctx, int fd, int efd, char*buf, int len);
void Add_Event(int epfd,int socket,int events)
{
    struct epoll_event ev;
    ev.data.fd = socket;
    ev.events = events;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, socket, &ev))
    {
        printf("epoll_ctl add error:%s\n", strerror(errno));
        exit(0);
    }
}
void Mod_Event(int epfd, int socket,int events)
{
    struct epoll_event ev;
    ev.data.fd = socket;
    ev.events = events;
    if (epoll_ctl(epfd, EPOLL_CTL_MOD, socket, &ev))
    {
        printf("epoll_ctl mod error:%s\n",strerror(errno));
        exit(0);
    }
}
void InitServer(int listen_socket)
{
    struct sockaddr_in server_addr;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    int opt = 1;
    if (setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        printf("setsockopt error:%s\n", strerror(errno));
        exit(0);
    }
    if (setsockopt(listen_socket, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)))
    {
        printf("setsockopt error:%s\n", strerror(errno));
        exit(0);
    }
    if (bind(listen_socket, (sockaddr*)&server_addr, sizeof(sockaddr_in)))
    {
        printf("bind error:%s\n", strerror(errno));
        exit(0);
    }
    if (listen(listen_socket, 5))
    {
        printf("listen error:%s\n", strerror(errno));
        exit(0);
    }
}
void AcceptConn(int epfd,int listen_socket)
{
    struct sockaddr_in client_addr;
    socklen_t clen;
    while (true)
    {
        int new_socket = accept(listen_socket, (sockaddr*)&client_addr, &clen);
        if (new_socket < 0)
        {
            if (errno != EAGAIN)
            {
                printf("accept error:%s\n", strerror(errno));
            }
            return;
        }
        Add_Event(epfd, new_socket, EPOLLET | EPOLLIN);
        fcntl(new_socket, F_SETFL, O_NONBLOCK | O_DIRECT);
        socket_bufs[new_socket] = new char[1024];//分配buffer
    }
}
void HandleFinishAio(int epfd,int efd, io_context_t ctx, io_event *events)
{
    uint64_t finished_aio;
    if (read(efd, &finished_aio, sizeof(finished_aio)) != sizeof(finished_aio)) //读出完成数量
    {
        printf("read error:%s\n", strerror(errno));
        return ;
    }
    struct timespec tms;
    while (finished_aio > 0)
    {
        tms.tv_nsec = 0;
        tms.tv_sec = 0;
        int ign = io_getevents(ctx, 1, CONN_N, events, &tms);
        for (int i = 0; i < ign; i++)
        {
            int fd = events[i].obj->aio_fildes;
            int compl_len = events[i].res;
            int success = events[i].res2;
            int compl_type = events[i].obj->aio_lio_opcode;
            char* buf = (char*)events[i].obj->u.c.buf;
            //接收数据完成
            if (compl_type == IO_CMD_PREAD)
            {
                if (success == 0)
                {
                    if (compl_len <= 0)
                    {
                        printf("recv data error:%s, and close socket\n", strerror(errno));
                        free(buf);                              //千万记得释放内存
                        close(fd);
                        continue;
                    }
                    printf("read bytes:%d\n", compl_len);
                    Mod_Event(epfd, fd, EPOLLET | EPOLLIN);     //继续读数据
                    SubmitWrite(ctx, fd, efd, buf, compl_len);  //把读取到的数据发会给客户端
                }
                else
                {
                    printf("read error:%s\n", strerror(errno));
                }
            }
            //数据发送完成
            else if (compl_type == IO_CMD_PWRITE)
            {
                if (success == 0)
                {
                    if (compl_len > 0)
                    {
                        printf("send data success len:%d\n", compl_len);
                    }
                }
                else
                {
                    printf("send data error:%s\n", strerror(errno));
                }
            }
        }
        finished_aio -= ign;
    }
}
void SubmitWrite(io_context_t ctx,int fd,int efd,char*buf,int len)
{
    iocb iocb1;
    iocb *ic = &iocb1;
    io_prep_pwrite(ic, fd, buf, len, 0);
    io_set_eventfd(ic, efd);
    int reio = io_submit(ctx, 1, &ic);
    if (reio != 1)  //提交异步IO任务
    {
        printf("write io_submit error:%s\n", strerror(-reio));
    }
}
void SubmitRead(io_context_t ctx, int fd, int efd, char*buf, int len)
{
    iocb iocb1;
    iocb *ic = &iocb1;
    io_prep_pread(ic, fd, buf, len, 0);
    io_set_eventfd(ic, efd);
    int reio = io_submit(ctx, 1, &ic);
    if (reio != 1)  //提交异步IO任务
    {
        printf("read io_submit error:%s\n", strerror(-reio));
    }
}
int main()
{
    int listen_socket = socket(AF_INET, SOCK_STREAM|SOCK_NONBLOCK|SOCK_CLOEXEC, 0);
    struct epoll_event epevents[EPEVNET_N];
    int epfd = epoll_create(1);
    if (epfd < 0)
    {
        printf("epoll_create error:%s\n", strerror(errno));
        exit(0);
    }

    Add_Event(epfd, listen_socket, EPOLLIN | EPOLLET);
    int efd= eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (efd<0)
    {
        printf("eventfd error:%s\n", strerror(errno));
        exit(0);
    }
    Add_Event(epfd, efd, EPOLLIN | EPOLLET);
    InitServer(listen_socket);
    io_context_t ctx = 0;
    if (io_setup(CONN_N, &ctx))
    {
        printf("io_setup error:%s\n", strerror(errno));
        exit(0);
    }
    io_event events[CONN_N];
    while (true)
    {
        int ret = epoll_wait(epfd, epevents, CONN_N, -1);
        if (ret <= 0)
        {
            printf("epoll_wait error:%s\n", strerror(errno));
        }
        if (ret > 0)
        {
            for (int i = 0; i < ret; i++)
            {
                //监听socket  接收连接 设置属性事件
                int fd = epevents[i].data.fd;
                if (fd == listen_socket)
                {
                    AcceptConn(epfd, listen_socket);
                }
                //异步管理fd 获取IO完成情况 根据读写完成情况进行处理
                else if (fd == efd)
                {
                    //HandleFinishAio(epfd, efd, ctx, events);  //TODO:封装进函数出现bug aio完成时的fd错误 原因尚未查明
                    uint64_t finished_aio;
                    if (read(efd, &finished_aio, sizeof(finished_aio)) != sizeof(finished_aio)) //读出完成数量
                    {
                        printf("read error:%s\n", strerror(errno));
                        return 0;
                    }
                    struct timespec tms;
                    while (finished_aio > 0)
                    {
                        tms.tv_nsec = 0;
                        tms.tv_sec = 0;
                        int ign = io_getevents(ctx, 1, CONN_N, events, &tms);
                        for (int i = 0; i < ign; i++)
                        {
                            int fd = events[i].obj->aio_fildes;
                            int compl_len = events[i].res;
                            int success = events[i].res2;
                            int compl_type = events[i].obj->aio_lio_opcode;
                            char* buf = (char*)events[i].obj->u.c.buf;
                            //接收数据完成
                            if (compl_type == IO_CMD_PREAD)
                            {
                                if (success == 0)
                                {
                                    if (compl_len <= 0)
                                    {
                                        printf("recv data error:%s, and close socket\n", strerror(errno));
                                        free(buf);                              //千万记得释放内存
                                        close(fd);
                                        continue;
                                    }
                                    printf("read bytes:%d\n", compl_len);
                                    Mod_Event(epfd, fd, EPOLLET | EPOLLIN);     //继续读数据
                                    SubmitWrite(ctx, fd, efd, buf, compl_len);  //把读取到的数据发会给客户端
                                }
                                else
                                {
                                    printf("read error:%s\n", strerror(errno));
                                }
                            }
                            //数据发送完成
                            else if (compl_type == IO_CMD_PWRITE)
                            {
                                if (success == 0)
                                {
                                    if (compl_len > 0)
                                    {
                                        printf("send data success len:%d\n", compl_len);
                                    }
                                }
                                else
                                {
                                    printf("send data error:%s\n", strerror(errno));
                                }
                            }
                        }
                        finished_aio -= ign;
                    }
                }
                //正常的conn socket 当有数据读写时进行提交IO任务
                else
                {
                    if (epevents[i].events&EPOLLIN)
                    {
                        SubmitRead(ctx, fd, efd, socket_bufs[fd], BUF_SIZE);
                    }
                }
            }
        }
    }
    return 0;
}
//注意点1：aio处理对方断开连接方式，res返回非正数。
//注意点2：io_content_t 的第一个参数，提交的io操作不能超过它（其实还可以略微多提交一些），
//io_getevents处理后会释放然后就可以重新提交
//注意点3：不可以像iocp先提交读再等待数据到来，会造成线程阻塞。
//注意点4：aio任务完成的顺序和提交顺序一致
//注意点5：像iocp一样在完成读io后，如果还有数据则继续注册读事件，r如果数据读完则无需,做法是设置epoll的event事件
//而不是重新io_submit（见第三点）
//注意点6：aio无法发送带外数据，使用同步io发送
//注意点7：aio进行io_submit之后在io完成前不能对iocb的元素进行修改，否则可能造成错误。
//注意点8：在提交写之后关闭socket，内核会根据socket的设定来决定是否发送数据。
//注意点9：无需取消io任务，可以根据io完成情况进行相对应处理。
//注意点10：注意信号SIGPIPE的处理，不然会中断程序的执行
