/*************************************************
Copyright (C) 2020-2030 PENDLE. All Rights Reserved
File name : storage.h
Author : pendle
Version : V1.0
Date : 20200914
Description : 存储模块的对外接口的头文件
Others:
History:
*************************************************/


#ifndef SRC_STORAGE_DATA_DEF_H_
#define SRC_STORAGE_DATA_DEF_H_

#include "storage_data_def.h"


//Storage模块的类，作为Storage模块的对外接口，统一处理Storage模块与外部模块的交互
class Storage
{
public:
    Storage();
    ~Storage();
};

#endif  //SRC_STORAGE_DATA_DEF_H_
