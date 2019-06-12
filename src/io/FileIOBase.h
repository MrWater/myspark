#ifndef __FILEIO_BASE_H__
#define __FILEIO_BASE_H__


#include <stdio.h>
#include <string.h>

#include "IIO.h"
#include "DataRowBase.h"
#include "exception/IOException.h"


namespace ns_io
{

enum class FileIOTypes : unsigned char
{
    READ = 0x01,
    WRITE = 0x02,
    READ_WRITE = 0x03,
    END = 0x04,
    APPEND = 0x08,
    TRUNCATE = 0x10,
    BINARY = 0x20
};

class FileIOBase : public IIO
{
public:
    FileIOBase(const char* filepath, size_t blockSize) 
        : _offset(0),
        _blockSize(blockSize),
        _ioType(FileIOTypes::READ) 
    {
        memcpy(_filepath, filepath, strlen(filepath)+1);
    }
    virtual ~FileIOBase() {}

    virtual bool open(FileIOTypes type=FileIOTypes::READ) throw(ns_exception::IOException) = 0;
    virtual size_t write(DataRowBase*) throw(ns_exception::IOException) = 0;
    virtual bool read(DataRowBase*) throw(ns_exception::IOException) = 0;
    virtual void close() throw(ns_exception::IOException) = 0;
    
    virtual void seek(size_t offset) { _offset = offset; }
    virtual const char* path() const { return _filepath; }

protected:
    size_t _offset;
    size_t _blockSize;
    char _filepath[1024];
    FileIOTypes _ioType;
};

}

#endif
