include config.mk

SUBDIRS = src/common src/container src/event src/exception src/task src/io src/scheduler src/thread src/net

all :
	@$(do_sub_dirs) "" $(SUBDIRS)

clean :
	@$(do_sub_dirs) clean $(SUBDIRS)
