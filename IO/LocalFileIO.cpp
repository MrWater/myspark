#include "LocalFileIO.h"


LocalFileIO::LocalFileIO(const char* filepath)
    : _filepath(filepath),
    _close(true),
    IOBase()
{
}

LocalFileIO::~LocalFileIO()
{
    if (!_close)
        _fs.close();
}

bool
LocalFileIO::open(IOTypes type)
{
    _iotype = type;

    switch(type)
    {
    case IOTypes::READ:
        _fs.open(_filepath, ios::in | ios::binary);
        break;
    case IOTypes::WRITE:
        _fs.open(_filepath, ios::out | ios::binary);
        break;
    case IOTypes::READ | IOTypes::WRITE:
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
    if ((_iotype & IOTypes::WRITE) == 0)
        throw IOException("cannot be written with read mode");

    int cnt = 0;

    for (int i = 0; i < frame.length(); ++i)
    {
        _fs.write(static_cast<char*>(&row), size);
        ++cnt;
    }

    _offset += cnt;

   return cnt;
}

bool
LocalFileIO::read(DataRowBase* row, size_t size)
{
    if ((_iotype & IOTypes::READ) == 0)
        throw IOException("cannot be written with write mode");

    _fs.read(static_cast<char*>(row), size);

    // TODO: return 
    return true;
}

void
LocalFileIO::close()
{
    
}
