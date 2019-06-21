#ifndef __HTTP_PROTOCOL_H__
#define __HTTP_PROTOCOL_H__


#include <map>
#include <vector>
#include <sstream>
#include <assert.h>

#include "HttpHeader.h"
#include "ProtocolBase.h"
#include "common/XString.h"


namespace ns_net
{

class HttpProtocol : public ProtocolBase
{
public:
    HttpProtocol()
    {
    }
    virtual ~HttpProtocol() {}

    virtual std::string serialize() const
    {
        std::ostringstream oss;
        oss << _method << " " << _uri << " " << _ver << "\n";
        
        HttpHeader temp  = _headers;
        HttpHeader::iterator iter = temp.begin();
        for(; iter != temp.end(); ++iter)
            oss << iter->first << ":" << iter->second << "\n";

        oss << "\n" << _data;
        
        return oss.str();
    }

    virtual void deserialize(std::string src)
    {
        std::vector<std::string> all = XString::split(src, "\n");
        assert(all.size() > 2);

        std::vector<std::string> firstLine = XString::split(all[0], " ");
        assert(firstLine.size() == 3);
        _method = firstLine[0];
        _uri = firstLine[1];
        _ver = firstLine[2];

        size_t idx;

        for (size_t i = 1; i < all.size()-2; ++i)
        {
            idx = all[i].find_first_of(":");
            assert(idx != std::string::npos);

            std::string key = all[i].substr(0, idx);
            std::string value = all[i].substr(idx+1);
            _headers[key] = value;
        }

        _data = all[all.size()-1];
    }

private:
    std::string _method;
    std::string _uri;
    std::string _ver;
    HttpHeader _headers;
    std::string _data;
};

}

#endif
