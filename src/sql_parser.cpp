/*************************************************
Copyright (C) 2020-2030 PENDLE. All Rights Reserved
File name : sql_parser.cpp
Author : pendle
Version : V1.0
Date : 20200914
Description : 解析用户输入的sql语句类所在的.cpp文件
Others:
History:
*************************************************/

#include "sql_parser.h"


/**
* @DESCRIPTION : sql语句入口类的构造函数
* @PARAM[IN] : input, 用户要执行的sql语句
*/
SqlParser::SqlParser(string input)
    :input_(input)
{
    //do nothing
}


/**
* @DESCRIPTION : sql语句入口类的析构函数
*/
SqlParser::~SqlParser()
{
    //do nothing
}


/**
* @DESCRIPTION : 对字符串input_进行检查，符合规范返回true,否则，返回false
* @RETURN : true/false, 字符串符合规范，返回true；否则，返回false
*/
bool SqlParser::CheckInput()
{
    string input(get_input());

    return true;
}
