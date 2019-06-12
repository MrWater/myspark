#include <iostream>

#include "LocalFileIO.h"
#include "TestDataRow.h"

using namespace std;
using namespace ns_io;
using namespace ns_exception;


LocalFileIO::LocalFileIO(const char* filepath, size_t blockSize)
    : _close(true),
    FileIOBase(filepath, blockSize)
{
}

LocalFileIO::~LocalFileIO()
{
    close();
}

bool
LocalFileIO::open(FileIOTypes type) throw(IOException)
{
    _ioType = type;

    switch(type)
    {
    case FileIOTypes::READ:
        _fs.open(_filepath, ios::in | ios::binary);
        break;
    case FileIOTypes::WRITE:
        _fs.open(_filepath, ios::out | ios::binary);
        break;
    case FileIOTypes::READ_WRITE:
        _fs.open(_filepath, ios::out | ios::in | ios::binary);
        break;
    // TODO: other types
    default:
        throw IOException("not permitted iotype");
    }

    return _fs;
}

size_t
LocalFileIO::write(DataRowBase* row) throw(IOException)
{
    if (((uint16_t)_ioType & (uint16_t)FileIOTypes::WRITE) == 0)
        throw IOException("cannot be written with read mode");

    _fs.write(reinterpret_cast<char*>(row), _blockSize);
    seek(++_offset);

   return 1;
}

bool
LocalFileIO::read(DataRowBase* row) throw(IOException)
{
    if (((uint16_t)_ioType & (uint16_t)FileIOTypes::READ) == 0)
        throw IOException("cannot be written with write mode");

    bool failed = _fs.read(reinterpret_cast<char*>(row), _blockSize);
    seek(++_offset);

    // TODO: return 
    return failed;
}

void
LocalFileIO::close() throw(IOException)
{
    if (_close)
        _fs.close();    
}

void
LocalFileIO::seek(size_t offset)
{
    FileIOBase::seek(offset);
    _fs.seekg(offset*_blockSize);
    _fs.seekp(offset*_blockSize);
}
