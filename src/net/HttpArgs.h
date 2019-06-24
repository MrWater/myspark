#ifndef __HTTP_ARGS_H__
#define __HTTP_ARGS_H__


#include <map>
#include <string>

#include "common/Iterateable.h"
#include "common/NotSequenceIterator.h"


namespace ns_net
{

class HttpArgs;

class HttpArgsIterator : public NotSequenceIterator<std::pair<const std::string, std::string>, \
                        typename std::map<std::string, std::string>::iterator>
{
public:
    virtual ~HttpArgsIterator() {}

private:
    HttpArgsIterator() {}
    friend class HttpArgs;
};

class HttpArgs : public Iterateable<std::pair<const std::string, std::string>, HttpArgsIterator>
{
public:
    HttpArgs() {}
    ~HttpArgs() {}

    std::string& operator[](std::string key)
    {
        return _data[key];
    }

    // TODO: other interface
    
    virtual HttpArgsIterator begin()
    {
        HttpArgsIterator iter;
        iter._iter = _data.begin();
        iter._current = &(*iter._iter);
        return iter;
    }

    virtual HttpArgsIterator end()
    {
        HttpArgsIterator iter;
        iter._iter = _data.end();
        iter._current = &(*iter._iter);
        return iter;
    }

private:
    std::map<std::string, std::string> _data;
};

}

#endif
