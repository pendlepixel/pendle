/*************************************************
Copyright (C) 2020-2030 PENDLE. All Rights Reserved
File name : unit_test_predefined.h
Author : pendle
Version : V1.0
Date : 20210108
Description : b+树部分单元测试的头文件
Others:
History:
*************************************************/

#ifndef PREDEFINED_H
#define PREDEFINED_H

#include <string.h>

namespace bpt
{

#define BP_ORDER 4

//key/value type
typedef int value_t;
struct key_t
{
    char k[16];
    key_t(const char* str = "")
    {
        memset(k, 0,sizeof(k));
        strcpy(k, str);
    }

    operator bool() const
    {
        return strcmp(k, "");
    }
};


inline int keycmp(const key_t&l, const key_t& r)
{
    return strcmp(l.k, r.k);
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
}  //namespace bpt

#endif  //PREDEFINED_H