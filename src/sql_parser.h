/*************************************************
Copyright (C) 2020-2030 PENDLE. All Rights Reserved
File name : sql_parser.h
Author : pendle
Version : V1.0
Date : 20200914
Description : 解析用户输入的sql语句类所在的头文件
Others:
History:
*************************************************/

#ifndef SRC_SQL_PARSER_H_
#define SRC_SQL_PARSER_H_

#include "data_def.h"


//进行语法分析的入口类，外界将要执行的sql语句，通过此类传递进来
class SqlParser
{
public:
    explicit SqlParser(string input);
    ~SqlParser();

    bool CheckInput();

private:
    void set_input(string in) { input_ = in; }
    string get_input() { return input_; }

    string input_;  //输入的要进行分析的sql语句字符串
};

#endif  //SRC_SQL_PARSER_H_
