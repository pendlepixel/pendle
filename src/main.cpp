/*************************************************
Copyright (C) 2020-2030 PENDLE. All Rights Reserved
File name : main.cpp
Author : pendle
Version : V1.0
Date : 20200914
Description : 数据库程序入口函数.cpp文件__
Others:
History:
*************************************************/

#include "data_def.h"
#include "sql_parser.h"


/**
* @DESCRIPTION : 程序入口函数
*/
int main(int argc, char** argv)
{
    string str = "create table if not exist `es_db_version` (\
            `verson_id` int(32) NOT NULL, \
            `version_number` int(32) NOT NULL); ";
    
    SqlParser parser(str);
    if (true == parser.CheckInput())
    {
        cout << boolalpha << true << endl;
    }
    else
    {
        cout << boolalpha << false << endl;
    }
    
    return 0;
}

