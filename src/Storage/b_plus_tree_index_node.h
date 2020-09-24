/*************************************************
Copyright (C) 2020-2030 PENDLE. All Rights Reserved
File name : b_plus_tree_index_node.h
Author : pendle
Version : V1.0
Date : 20200922
Description : b+树的索引结点的相关的头文件
Others:
History:
*************************************************/


#ifndef SRC_B_PLUS_TREE_INDEX_NODE_H_
#define SRC_B_PLUS_TREE_INDEX_NODE_H_

#include "storage_data_def.h"


//b+树索引结点(非叶子结点)
class BPlusIndexNode
{
public:
    BPlusIndexNode();
    ~BPlusIndexNode();

    bool InsertIntoNode(const string value);
    bool IndexNodeDivide(string& divideValue, list<string>& firstDivideNode, 
        list<string>& secondDivideNode);

private:
    bool NodeNumIncrease();
    bool NodeNumDecrease();

    list<string> GetNode() { return node_; }
    void SetNode(list<string>& node) { node_ = node; }
    int GetNodeNum() { return nodeNum_; }
    void SetNodeNum(int num) { nodeNum_ = num; }
    
    list<string> node_;  //一个索引结点
    int nodeNum_;  //当前的索引节点中的节点数
};





#endif  //SRC_B_PLUS_TREE_INDEX_NODE_H_
