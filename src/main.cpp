//主程序开始的入口文件
#include "data_def.h"
#include "sql_parser.h"


//整个程序的入口函数，从这里开始
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

