/*************************************************
Copyright (C) 2020-2030 PENDLE. All Rights Reserved
File name : b_plus_tree_leaf_node.cpp
Author : pendle
Version : V1.0
Date : 20200922
Description : b+树的结点的实现相关的.cpp文件，包含b+树的一些基本操作的具体细节
Others:
History:
*************************************************/


#include "b_plus_tree_leaf_node.h"
#include "storage_data_def_inner.h"


/**
* @DESCRIPTION : 叶子节点类的构造函数
*/
BPlusLeafNode::BPlusLeafNode()
    : nodeNum_(0)
{
    
}


/**
* @DESCRIPTION : 叶子节点类的析构函数
*/
BPlusLeafNode::~BPlusLeafNode()
{

}


bool BPlusLeafNode::NodeNumIncrease()
{
    int num = GetNodeNum();
    num += 1;
    SetNodeNum(num);

    if (num > tree::nodeNumMax)
    {
        return false;
    }
    else
    {
        return true;
    }
    
}


bool BPlusLeafNode::NodeNumDecrease()
{
    int num = GetNodeNum();
    num -= 1;
    SetNodeNum(num);

    if (num < tree::nodeNumMin)
    {
        return false;
    }
    else
    {
        return true;
    }
}


bool BPlusLeafNode::InsertIntoNode(const string value)
{
    list<string> node(GetNode());

    for (list<string>::iterator iter = node.begin(); node.end() != iter; ++iter)
    {
        string str = *iter;
        if (value < str)
        {
            node.insert(iter, value);
            NodeNumIncrease();
        }
    }

    return true;
}