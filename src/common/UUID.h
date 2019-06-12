#ifndef __UUID_H__
#define __UUID_H__


#include <string>
#include <sstream>
#include <iomanip>
#include <uuid/uuid.h>


class UUID
{
public:
    UUID() { uuid_generate(_u); }
    ~UUID() {}

    operator std::string() const
    {
        char id[36];
        uuid_unparse(_u, id);        

        return id;
    }

private:
    uuid_t _u;
};

#endif
