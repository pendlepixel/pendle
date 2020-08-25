//解析用户输入的部分
#ifndef SRC_SQL_PARSER_H_
#define SRC_SQL_PARSER_H_

#include "data_def.h"

class SqlParser
{
public:
    explicit SqlParser(string input);
    ~SqlParser();

    bool CheckInput();

private:
    void set_input(string in) { input_ = in; }
    string get_input() { return input_; }

    string input_;
};

#endif  //SRC_SQL_PARSER_H_