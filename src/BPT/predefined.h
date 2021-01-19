/*************************************************
Copyright (C) 2020-2030 PENDLE. All Rights Reserved
File name : predefined.h
Author : pendle
Version : V1.0
Date : 20210108
Description : b+树额外相关部分的头文件
Others:
History:
*************************************************/

#ifndef PREDEFINED_H
#define PREDEFINED_H

#include <string.h>

namespace bpt {

#define BP_ORDER 20

/*key/value type*/
typedef int value_t;
struct key_t
{
    char k[16];

    key_t(const char* str = "")
    {
        bzero(k, sizeof(k));
        strcpy(k, str);
    }

    operator bool() const 
    {
        return strcmp(k, "");
    }
};


inline int keycmp(const key_t& a, const key_t& b)
{
    int x = strlen(a.k) - strlen(b.k);
    return x == 0 ? strcmp(a.k, b.k) : x;
}

#define OPERATOR_KEYCMP(type) \
    bool operator< (const key_t& l, const type& r) {\
        return keycmp(l, r.key) < 0;\
    }\
    bool operator< (const type& l, const key_t& r) {\
        return keycmp(l.key, r) < 0;\
    }\
    bool operator== (const key_t& l, const type& r) {\
        return keycmp(l, r.key) == 0;\
    }\
    bool operator== (const type& l, const key_t& r) {\
        return keycmp(l.key, r) == 0;\
    }
}

#endif