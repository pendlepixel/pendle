/*************************************************
Copyright (C) 2020-2030 PENDLE. All Rights Reserved
File name : cli.cpp
Author : pendle
Version : V1.0
Date : 20210108
Description : b+树部分单元测试的.cpp文件
Others:
History:
*************************************************/

#include "../bpt.h"
using namespace bpt;

#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s database command\n", argv[0]);
        return 1;
    }

    bpt::bplus_tree database(argv[1]);
    if (0 == strcmp(argv[2], "search"))
    {
        if (argc <4)
        {
            fprintf(stderr, "Need key.\n");
            return 1;
        }

        if (4 == argc)
        {
            value_t value;
            if (0 != database.search(argv[3], &value))
            {
                printf("Key %s not found.\n", argv[3]);
            }
            else
            {
                printf("%d\n", value);
            }
        }
        else
        {
            bpt::key_t start(argv[3]);
            value_t values[512];
            bool next = true;
            while(next)
            {
                int ret = database.search_range(&start, argv[4], values, 512, &next);
                if (ret < 0)
                {
                    break;
                }

                for (int i = 0; i < ret; i++)
                {
                    printf("%d\n", values[i]);
                }
            }
        }
    }
    else if (0 == strcmp(argv[2], "insert"))
    {
        if (5 != argc)
        {
            fprintf(stderr, "Format is [insert key value]\n");
            return 1;
        }

        if (0 != database.insert(argv[3], atoi(argv[4])))
        {
            printf("Key %s already exists.\n", argv[3]);
        }
    }
    else if (0 == strcmp(argv[2], "update"))
    {
        if (5 != argc)
        {
            fprintf(stderr, "Format is [update key value]\n");
            return 1;
        }

        if (0 != database.update(argv[3], atoi(argv[4])))
        {
            printf("Key %s does not exist.\n", argv[3]);
        }
    }
    else
    {
        fprintf(stderr, "Invalid command: %s\n", argv[2]);
        return 1;
    }

    return 0;
}







