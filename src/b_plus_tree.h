/*************************************************
Copyright (C) 2020-2030 PENDLE. All Rights Reserved
File name : b_plus_tree.h
Author : pendle
Version : V1.0
Date : 20200914
Description : b+树的实现相关的头文件，本数据库使用存储数据结构为b+树
Others:
History:
*************************************************/

#ifndef SRC_B_PLUS_TREE_H_
#define SRC_B_PLUS_TREE_H_

#include "data_def.h"


//b+树的实现类，此类中包含b+树的创建、插入节点和删除节点等基本操作
class BPlusTree
{
public:
    BPlusTree();
    ~BPlusTree();

    void Init();  //初始化，创建树的接口

    void Insert();
    void Delete();
    

private:    
};


//b+树节点的类，包含一些基本的b+树节点信息
class BPlusTreeNode
{
public:
    BPlusTreeNode() {};
    ~BPlusTreeNode() {};

private:

};

#endif  //SRC_B_PLUS_TREE_H_
