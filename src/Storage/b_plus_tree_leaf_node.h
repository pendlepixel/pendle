/*************************************************
Copyright (C) 2020-2030 PENDLE. All Rights Reserved
File name : b_plus_tree_leaf_node.h
Author : pendle
Version : V1.0
Date : 20200922
Description : b+树的索引结点的相关的头文件
Others:
History:
*************************************************/


#ifndef SRC_B_PLUS_TREE_LEAF_NODE_H_
#define SRC_B_PLUS_TREE_LEAF_NODE_H_

#include "storage_data_def.h"


//b+树叶子结点
class BPlusLeafNode
{
public:
    BPlusLeafNode();
    ~BPlusLeafNode();

    bool InsertIntoNode(const string value);

private:    
    bool NodeNumIncrease();
    bool NodeNumDecrease();

    list<string> GetNode() { return node_; }
    void SetNode(list<string>& node) { node_ = node; }
    int GetNodeNum() { return nodeNum_; }
    void SetNodeNum(int num) { nodeNum_ = num; }
    
    list<string> node_;  //一个叶子结点
    int nodeNum_;  //当前的叶子节点中的节点数
};


#endif  //SRC_B_PLUS_TREE_LEAF_NODE_H_
