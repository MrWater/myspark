#ifndef __LOCALFILE_IO_H__
#define __LOCALFILE_IO_H__


#include <fstream>

#include "FileIOBase.h"


namespace ns_io
{

class LocalFileIO : public FileIOBase
{
public:
    LocalFileIO(const char* filepath, size_t blockSize);
    virtual ~LocalFileIO();

    virtual bool open(FileIOTypes type=FileIOTypes::READ) throw(ns_exception::IOException);
    virtual size_t write(DataRowBase*) throw(ns_exception::IOException);
    virtual bool read(DataRowBase*) throw(ns_exception::IOException);
    virtual void close() throw(ns_exception::IOException);

    virtual void seek(size_t);

private:
    std::fstream _fs;
    bool _close;
};

}

#endif
