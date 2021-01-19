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

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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
typedef struct {
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
    key_t key;
    off_t child;  //子节点的偏移量
};


//内部结点的结构
struct internal_node_t {
    typedef index_t* child_t;

    off_t parent;  //父节点的偏移量
    off_t next;  //下一个内部结点的偏移量
    off_t prev;  //前一个内部结点的偏移量
    size_t n;  //子节点的个数
    index_t children[BP_ORDER];
};


//单个叶子结点的结构
struct record_t {
    key_t key;
    value_t value;
};


//叶子结点的结构
struct leaf_node_t {
    typedef record_t* child_t;

    off_t parent;  //叶子结点的父节点
    off_t next;  //下一个叶子结点
    off_t prev;  //上一个叶子结点
    size_t n;    //
    record_t children[BP_ORDER];
};


//b+树的
class bplus_tree {
public:
    bplus_tree(const char* path, bool force_empty = false);

    //
    int search(const key_t& key, value_t* value) const;
    int search_range(key_t* left, const key_t& right,
        value_t* values, size_t max, bool* next = NULL) const;
    int remove(const key_t& key);
    int insert(const key_t& key, value_t value);
    int update(const key_t& key, value_t value);
    meta_t get_meta() const {
        return meta;
    };

#ifndef UNIT_TEST
private:
#else
public:
#endif
    char path[512];
    meta_t meta;

    //初始化空树
    void init_from_empty();

    //find index
    off_t search_index(const key_t& key) const;

    //find leaf
    off_t search_leaf(off_t index, const key_t& key) const;
    off_t search_leaf(const key_t& key) const
    {
        return search_leaf(search_index(key), key);
    }

    //remove internal node
    void remove_from_index(off_t offset, internal_node_t& node,
        const key_t& key);
    
    //borrow one key from other internal node
    bool borrow_key(bool from_right, internal_node_t& borrower,
        off_t offset);

    // borrow one record from other leaf
    bool borrow_key(bool from_right, leaf_node_t &borrower);

    //change one's parent key to another key
    void change_parent_child(off_t parent, const key_t& o, 
        const key_t& n);

    //merge right leaf to left leaf
    void merge_leafs(leaf_node_t* left, leaf_node_t* right);
    
    void merge_keys(index_t* where, internal_node_t& left,
        internal_node_t& right, bool change_where_key = false);
    
    //insert into leaf without split
    void insert_record_no_split(leaf_node_t* leaf, const key_t& key,
        const value_t& value);

    //add key to the internal node
    void insert_key_to_index(off_t offset, const key_t& key,
        off_t value, off_t after);
    void insert_key_to_index_no_split(internal_node_t& node, 
        const key_t& key, off_t value);

    //change children's parent
    void reset_index_children_parent(index_t* begin, index_t* end,
        off_t parent);

    template<class T>
    void node_create(off_t offset, T *node, T *next);

    template<class T>
    void node_remove(T* prev, T* node);

    //multi-level file open/close
    mutable FILE* fp;
    mutable int fp_level;
    void open_file(const char* mode = "rb+") const
    {
        //`rb+` will make sure we can write everywhere without truncating file
        if (fp_level == 0)
            fp = fopen(path, mode);

        ++fp_level;
    }

    void close_file() const
    {
        if (fp_level == 1)
            fclose(fp);

        --fp_level;
    }

    //alloc from disk
    off_t alloc(size_t size)
    {
        off_t slot = meta.slot;
        meta.slot += size;
        return slot;
    }

    off_t alloc(leaf_node_t* leaf)
    {
        leaf->n = 0;
        meta.leaf_node_num++;
        return alloc(sizeof(leaf_node_t));
    }

    off_t alloc(internal_node_t* node)
    {
        node->n = 1;
        meta.internal_node_num++;
        return alloc(sizeof(internal_node_t));
    }

    void unalloc(leaf_node_t* leaf, off_t offset)
    {
        --meta.leaf_node_num;
    }

    void unalloc(internal_node_t* node, off_t offset)
    {
        --meta.internal_node_num;
    }

    //read block from disk
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

    //write block to disk
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
    
};

}

#endif  //BPT_H