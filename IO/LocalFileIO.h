#ifndef __LOCALFILE_IO_H__
#define __LOCALFILE_IO_H__


#include <fstream>

#include "FileIOBase.h"


namespace ns_io
{

class LocalFileIO : public FileIOBase
{
public:
    LocalFileIO(const char* filepath);
    virtual ~LocalFileIO();

    virtual bool open(FileIOTypes type=FileIOTypes::READ) throw(ns_exception::IOException);
    virtual size_t write(const DataRowBase&, size_t) throw(ns_exception::IOException);
    virtual bool read(DataRowBase*, size_t) throw(ns_exception::IOException);
    virtual void close() throw(ns_exception::IOException);

private:
    const char* _filepath;
    std::fstream _fs;
    bool _close;
};

}

#endif
