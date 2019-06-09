#include <iostream>

#include "LocalFileIO.h"

using namespace std;
using namespace ns_io;
using namespace ns_exception;


LocalFileIO::LocalFileIO(const char* filepath)
    : _filepath(filepath),
    _offset(0),
    _ioType(FileIOTypes::READ),
    _close(true)
{
}

LocalFileIO::~LocalFileIO()
{
    if (!_close)
        _fs.close();
}

bool
LocalFileIO::open(FileIOTypes type)
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
    case FileIOTypes::READ | FileIOTypes::WRITE:
        _fs.open(_filepath, ios::in | ios::out | ios::binary);
        break;
    // TODO: other types
    default:
        throw IOException("not permitted iotype");
    }

    return _fs.is_open();
}

size_t
LocalFileIO::write(const DataRowBase& row, size_t size)
{
    if ((_ioType & FileIOTypes::WRITE) == 0)
        throw IOException("cannot be written with read mode");

    int cnt = 0;

    _fs.write(reinterpret_cast<char*>(const_cast<DataRowBase*>(&row)), size);
    ++cnt;

    _offset += cnt;

   return cnt;
}

bool
LocalFileIO::read(DataRowBase* row, size_t size)
{
    if ((_ioType & FileIOTypes::READ) == 0)
        throw IOException("cannot be written with write mode");

    _fs.read(reinterpret_cast<char*>(row), size);

    // TODO: return 
    return true;
}

void
LocalFileIO::close()
{
    
}
