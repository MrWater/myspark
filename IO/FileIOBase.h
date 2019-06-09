#ifndef __FILEIO_BASE_H__
#define __FILEIO_BASE_H__


#include <stdio.h>

#include "IIO.h"
#include "DataRowBase.h"
#include "Exception/IOException.h"


namespace ns_io
{

enum class FileIOTypes : unsigned char
{
    READ = 0x01,
    WRITE = 0x02,
    END = 0x04,
    APPEND = 0x08,
    TRUNCATE = 0x10,
    BINARY = 0x20
};

class FileIOBase : public IIO
{
public:
    virtual bool open(FileIOTypes type=FileIOTypes::READ) throw(ns_exception::IOException) = 0;
    virtual size_t write(const DataRowBase&, size_t) throw(ns_exception::IOException) = 0;
    virtual bool read(DataRowBase*, size_t) throw(ns_exception::IOException) = 0;
    virtual void close() throw(ns_exception::IOException) = 0;
    virtual void seek(size_t offset) { _offset = offset; }

protected:
    size_t _offset;
    FileIOTypes _ioType;
};

}

#endif
