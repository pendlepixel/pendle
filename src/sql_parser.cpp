#include "sql_parser.h"


SqlParser::SqlParser(string input)
    :input_(input)
{
    //do nothing
}


SqlParser::~SqlParser()
{
    //do nothing
}


bool SqlParser::CheckInput()
{
    string input(get_input());

    return true;
}
