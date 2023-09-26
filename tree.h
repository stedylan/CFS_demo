#include <stdio.h>
#include <stdlib.h>

// 定义二叉查找树节点
struct bst_node {
    int pid;
    int value;
    struct bst_node* left;
    struct bst_node* right;
};

// 创建新节点
struct bst_node* create_node(int pid, int value);

// 插入节点
struct bst_node* insert(struct bst_node* root, int pid, int value);

// 删除最小节点并返回pid
int delete_min(struct bst_node** root);

// 中序遍历并打印节点信息
void inorder_traversal(struct bst_node* root);

// 销毁二叉查找树
void destroy_tree(struct bst_node* root);
