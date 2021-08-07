/*************************************************
Copyright (C) 2020-2030 PENDLE. All Rights Reserved
File name : bpt.h
Author : pendle
Version : V1.0
Date : 20210108
Description : b+树实现的头文件
Others:
History:
*************************************************/

#ifndef BPT_H
#define BPT_H

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cassert>

//放开和屏蔽控制是否进行单元测试，放开这个宏，进行单元测试；屏蔽这个宏，不进行单元测试
//#define UNIT_TEST

#ifndef UNIT_TEST
#include "predefined.h"
#else
#include "util/unit_test_predefined.h"
#endif

namespace bpt {

/*offsets */
#define OFFSET_META 0
#define OFFSET_BLOCK OFFSET_META + sizeof(meta_t)
#define SIZE_NO_CHILDREN sizeof(leaf_node_t) - BP_ORDER * sizeof(record_t)


//b+树数据结构模型
typedef struct 
{
    size_t order;  //
    size_t value_size;  //value的size
    size_t key_size;  //key的size
    size_t internal_node_num;  //内部结点的个数
    size_t leaf_node_num;  //叶子结点的个数
    size_t height;  //树的高度
    off_t slot;         //保存新结点的偏移量
    off_t root_offset;  //根节点的偏移量
    off_t leaf_offset;  //第一个叶子结点的偏移量
}meta_t;


//单个内部结点的结构
struct index_t {
    key_t key;  //单个内部节点的key值
    off_t child;  //单个内部节点在内部节点中的偏移量
};


//内部结点的结构
struct internal_node_t 
{
    typedef index_t* child_t;

    off_t parent;  //父节点的偏移量
    off_t next;  //下一个内部结点的偏移量
    off_t prev;  //前一个内部结点的偏移量
    size_t n;  //子节点的个数
    index_t children[BP_ORDER];  //每个单个节点的内容
};


//单个叶子结点的结构
struct record_t {
    key_t key;  //单个叶子节点的key值
    value_t value;  //单个叶子结点在叶子结点中的偏移量
};


//叶子结点的结构
struct leaf_node_t 
{
    typedef record_t* child_t;

    off_t parent;  //叶子结点的父节点
    off_t next;  //下一个叶子结点
    off_t prev;  //上一个叶子结点
    size_t n;    //子节点的个数
    record_t children[BP_ORDER];  //每个单个节点的内容
};


//b+树的
class bplus_tree 
{
public:
    bplus_tree(const char* path, bool force_empty = false);

    //
    int search(const key_t& key, value_t* value) const;
    int search_range(key_t* left, const key_t& right,
        value_t* values, size_t max, bool* next = NULL) const;
    int remove(const key_t& key);
    int insert(const key_t& key, value_t value);  //插入一个新的结点
    int update(const key_t& key, value_t value);  //更新一个新的结点
    meta_t get_meta() const { return meta; };

#ifndef UNIT_TEST
private:
#else
public:
#endif

    //初始化空树
    void init_from_empty();

    //查找索引节点的偏移量
    off_t search_index(const key_t& key) const;

    //查找叶子结点的偏移量
    off_t search_leaf(off_t index, const key_t& key) const;
    off_t search_leaf(const key_t& key) const
    {
        return search_leaf(search_index(key), key);
    }

    //删除某个索引节点
    void remove_from_index(off_t offset, internal_node_t& node, const key_t& key);
    
    //borrow one key from other internal node
    bool borrow_key(bool from_right, internal_node_t& borrower, off_t offset);

    // borrow one record from other leaf
    bool borrow_key(bool from_right, leaf_node_t &borrower);

    //change one's parent key to another key
    void change_parent_child(off_t parent, const key_t& o, const key_t& n);

    //merge right leaf to left leaf
    void merge_leafs(leaf_node_t* left, leaf_node_t* right);
    
    void merge_keys(index_t* where, internal_node_t& left,
        internal_node_t& right, bool change_where_key = false);
    
    //insert into leaf without split
    void insert_record_no_split(leaf_node_t* leaf, const key_t& key, const value_t& value);

    //add key to the internal node
    void insert_key_to_index(off_t offset, const key_t& key, off_t value, off_t after);
    void insert_key_to_index_no_split(internal_node_t& node, const key_t& key, off_t value);

    //change children's parent
    void reset_index_children_parent(index_t* begin, index_t* end, off_t parent);

    template<class T>
    void node_create(off_t offset, T *node, T *next);

    template<class T>
    void node_remove(T* prev, T* node);

    //multi-level file open/close
    void open_file(const char* mode = "rb+") const
    {
        //`rb+` will make sure we can write everywhere without truncating file
        if (0 == fp_level)
        {
            fp = fopen(path, mode);
        }

        ++fp_level;
    }

    void close_file() const
    {
        if (1 == fp_level)
        {
            fclose(fp);
        }

        --fp_level;
    }

    //申请磁盘空间
    off_t alloc(size_t size)
    {
        off_t slot = meta.slot;
        meta.slot += size;
        return slot;
    }

    //为叶子结点申请空间
    off_t alloc(leaf_node_t* leaf)
    {
        leaf->n = 0;
        meta.leaf_node_num++;
        return alloc(sizeof(leaf_node_t));
    }

    //为非叶子结点申请空间
    off_t alloc(internal_node_t* node)
    {
        node->n = 1;
        meta.internal_node_num++;
        return alloc(sizeof(internal_node_t));
    }

    //释放叶子结点占用的空间
    void unalloc(leaf_node_t* leaf, off_t offset)
    {
        --meta.leaf_node_num;
    }

    //释放非叶子结点占用的空间
    void unalloc(internal_node_t* node, off_t offset)
    {
        --meta.internal_node_num;
    }

    //从磁盘中读取内容
    int map(void* block, off_t offset, size_t size) const
    {
        open_file();
        fseek(fp, offset, SEEK_SET);
        size_t rd = fread(block, size, 1, fp);
        close_file();

        return rd - 1;
    }

    template<class T>
    int map(T* block, off_t offset) const
    {
        return map(block, offset, sizeof(T));
    }

    //向磁盘中写入内容
    int unmap(void* block, off_t offset, size_t size) const
    {
        open_file();
        fseek(fp, offset, SEEK_SET);
        size_t wd = fwrite(block, size, 1, fp);
        close_file();

        return wd - 1;
    }

    template<class T>
    int unmap(T* block, off_t offset) const
    {
        return unmap(block, offset, sizeof(T));
    }

    char path[PATH_MAX_SIZE];  //存放数据的文件目录
    meta_t meta;  //整个树节点
    mutable FILE* fp;  //文件句柄
    mutable int fp_level;  //标记文件打开次数
    
};

}

#endif  //BPT_H