#ifndef __XSTRING_H__
#define __XSTRING_H__


#include <vector>
#include <string>
#include <string.h>

class XString final
{
public:
    static std::vector<std::string> split(const std::string& src, \
            char sep)
    {
        std::vector<std::string> ret;
        size_t pos1 = 0;
        size_t pos2 = src.find_first_of(sep);
        
        while (pos2 != std::string::npos)
        {
            ret.push_back(src.substr(pos1, pos2-pos1));
            pos1 = pos2 + 1;

            if (pos1 >= src.length())
            {
                ret.push_back("");
                break;
            }

            pos2 = src.substr(pos1).find_first_of(sep);
            
            if (pos2 != std::string::npos)
                pos2 += pos1;
        }

        if (pos1 < src.length())
            ret.push_back(src.substr(pos1));

        return ret;
    }

private:
    XString() {}
    ~XString() {}
};


#endif
