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


/**
* @DESCRIPTION : 叶子结点计数加一
* @RETURN : true/false. 增加之后，不超过阶数，返回true；超过阶数，返回false
*/
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


/**
* @DESCRIPTION : 叶子结点计数减一
* @RETURN : true/false. 减少之后，大于最小值，返回true；否则，返回false
*/
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


/**
* @DESCRIPTION : 向叶子结点插入一个元素
* @PARAM[IN] : value, 要插入的元素的值
* @RETURN : true/false. 插入元素之后，结点符合要求，返回true;否则，返回false
*/
bool BPlusLeafNode::InsertIntoNode(const string value)
{
    list<string> node(GetNode());

    for (list<string>::const_iterator iter = node.cbegin(); node.cend() != iter; ++iter)
    {
        string str = *iter;
        if (value < str)
        {
            node.insert(iter, value);
            return NodeNumIncrease();
        }
    }

    return true;
}


/**
* @DESCRIPTION : 叶子结点分裂成两个叶子结点，并返回分裂线处的元素内容
* @PARAM[OUT] : divideValue, 分裂线处的元素内容
* @PARAM[OUT] : firstDivideNode, 分裂之后的第一个叶子结点
* @PARAM[OUT] : secondDivideNode, 分裂之后的第二个叶子结点
* @RETURN : true/false. 插入元素之后，结点符合要求，返回true;否则，返回false
*/
bool BPlusLeafNode::LeafNodeDivide(string& divideValue, list<string>& firstDivideNode, 
    list<string>& secondDivideNode)
{
    //结点元素个数不超过限定值，不进行分裂
    if (GetNodeNum() <= tree::nodeNumMax)
    {
        return false;
    }

    list<string> node(GetNode());
    list<string>::const_iterator iter = node.cbegin();
    for (int i = 0; i < node.size(); i++, ++iter)
    {
        if (i < (node.size() / 2))
        {
            firstDivideNode.push_back(*iter);
        }
        else if (i > (node.size() / 2))
        {
            secondDivideNode.push_back(*iter);
        }
        else
        {
            divideValue = *iter;
        }
    }

    return true;
}