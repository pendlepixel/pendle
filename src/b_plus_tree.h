/*************************************************
Copyright (C) 2020-2030 PENDLE. All Rights Reserved
File name : b_plus_tree.h
Author : pendle
Version : V1.0
Date : 20200914
Description : b+树的实现相关的头文件，本数据库使用存储数据结构为b+树
              https://www.jianshu.com/p/e4f9680e531a
              https://www.cnblogs.com/lianzhilei/p/11250589.html
Others:
History:
*************************************************/


#ifndef SRC_B_PLUS_TREE_H_
#define SRC_B_PLUS_TREE_H_

#include "data_def.h"
#include "b_plus_tree_index_node.h"
#include "b_plus_tree_leaf_node.h"


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
    list<BPlusIndexNode> indexNodes_;  //树的索引节点集合 
    list<BPlusLeafNode> leafNodes_;  //指向第一个叶子结点的指针
    const int limitNum_ = 4;  //4阶b+树
};


//判断结点是否超过了最大阶数限制
bool CheckIfExceedLimitNum(BPlusIndexNode& indexNode);
bool CheckIfExceedLimitNum(BPlusLeafNode& leafNode);

#endif  //SRC_B_PLUS_TREE_H_
