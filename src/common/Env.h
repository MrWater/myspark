#ifndef __ENV_H__
#define __ENV_H__


bool isLittleEndian() 
{ 
    short var = 0x0001; 
    return *((char*)&var) == 0x01;
}

#endif
