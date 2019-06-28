#ifndef __HTTP_HEADER_H__
#define __HTTP_HEADER_H__


#include <map>
#include <string>

#include "common/Iterateable.h"
#include "common/NotSequenceIterator.h"


namespace ns_net
{

class HttpHeader;

class HttpHeaderIterator : public NotSequenceIterator<std::pair<const std::string, std::string>, \
                        typename std::map<std::string, std::string>::iterator>
{
public:
    virtual ~HttpHeaderIterator() {}

private:
    HttpHeaderIterator() {}
    friend class HttpHeader;
};

class HttpHeader : public Iterateable<std::pair<const std::string, std::string>, HttpHeaderIterator>
{
public:
    HttpHeader() {}
    ~HttpHeader() {}

    std::string& operator[](std::string key)
    {
        return _data[key];
    }

    // TODO: other interface
    
    virtual HttpHeaderIterator begin()
    {
        HttpHeaderIterator iter;
        iter._iter = _data.begin();
        iter._current = &(*iter._iter);
        return iter;
    }

    virtual HttpHeaderIterator end()
    {
        HttpHeaderIterator iter;
        iter._iter = _data.end();
        iter._current = &(*iter._iter);
        return iter;
    }

    void clear()
    {
        _data.clear();
    }

private:
    std::map<std::string, std::string> _data;
};

}

#endif
