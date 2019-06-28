#ifndef __HTTP_REQUEST_PROTOCOL_H__
#define __HTTP_REQUEST_PROTOCOL_H__


#include <map>
#include <vector>
#include <sstream>
#include <assert.h>

#include "HttpArgs.h"
#include "HttpHeader.h"
#include "ProtocolBase.h"
#include "common/XString.h"


namespace ns_net
{

class HttpRequestProtocol : public ProtocolBase
{
public:
    HttpRequestProtocol()
    {
    }
    virtual ~HttpRequestProtocol() {}

    virtual std::string serialize() const
    {
        std::ostringstream oss;
        oss << _method << " " << _uri << " " << _ver << "\n";
        
        HttpHeader temp  = _headers;
        HttpHeader::iterator iter = temp.begin();
        for(; iter != temp.end(); ++iter)
            oss << iter->first << ":" << iter->second << "\n";

        oss << "\n" << _data;

        /*HttpArgs args = _args;
        HttpArgs::iterator iter2 = args.begin();
        oss << "\nargs:";
        for(; iter2 != args.end(); ++iter2)
            oss << iter2->first << "=" << iter2->second << "\n";*/
        
        return oss.str();
    }

    virtual void deserialize(std::string src)
    {
        std::vector<std::string> all = XString::split(src, '\n');
        assert(all.size() > 2);

        std::vector<std::string> firstLine = XString::split(all[0], ' ');
        assert(firstLine.size() == 3);

        _method = firstLine[0];
        _uri = firstLine[1];
        _ver = firstLine[2];

        size_t idx = _uri.find_last_of("?");
        std::string key = "";
        std::string value = "";

        if (idx != std::string::npos)
        {
            // TODO: optimize
            std::vector<std::string> args = XString::split(_uri.substr(idx+1), '&');
            for (size_t i = 0; i < args.size(); ++i)
            {
                idx = args[i].find_first_of("=");
                
                if (idx == std::string::npos)
                    _args[args[i]] = "";
                else
                    _args[args[i].substr(0, idx)] = args[i].substr(idx+1);
            }
        }

        for (size_t i = 1; i < all.size()-2; ++i)
        {
            idx = all[i].find_first_of(":");
            assert(idx != std::string::npos);

            key = all[i].substr(0, idx);
            value = all[i].substr(idx+1);
            _headers[key] = value;
        }

        _data = all[all.size()-1];
    }

    virtual void clear()
    {
        _method = "";
        _uri = "";
        _ver = "";
        _args.clear();
        _headers.clear();
        _data = "";
    }

private:
    std::string _method;
    std::string _uri;
    std::string _ver;
    HttpArgs _args;
    HttpHeader _headers;
    std::string _data;
};

}

#endif
