#include "tree.h"


// 创建新节点
struct bst_node *create_node(int pid, int value)
{
    struct bst_node *new_node = (struct bst_node *)malloc(sizeof(struct bst_node));
    if (new_node == NULL)
    {
        perror("无法分配内存");
        exit(EXIT_FAILURE);
    }
    new_node->pid = pid;
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// 插入节点
struct bst_node *insert(struct bst_node *root, int pid, int value)
{
    if (root == NULL)
    {
        return create_node(pid, value);
    }

    if (value < root->value)
    {
        root->left = insert(root->left, pid, value);
    }
    else
    {
        root->right = insert(root->right, pid, value);
    }

    return root;
}

// 删除最小节点并返回pid
int delete_min(struct bst_node **root)
{
    if (*root == NULL)
    {
        printf("树为空，无法删除最小节点\n");
        exit(EXIT_FAILURE);
    }

    struct bst_node *current = *root;
    struct bst_node *parent = NULL;

    while (current->left != NULL)
    {
        parent = current;
        current = current->left;
    }

    int deleted_pid = current->pid;

    if (parent == NULL)
    {
        // 当前最小节点是根节点
        *root = current->right;
    }
    else
    {
        parent->left = current->right;
    }

    free(current);
    return deleted_pid;
}

// 中序遍历并打印节点信息
void inorder_traversal(struct bst_node *root)
{
    if (root != NULL)
    {
        inorder_traversal(root->left);
        printf("PID: %d, Value: %d\n", root->pid, root->value);
        inorder_traversal(root->right);
    }
}

// 销毁二叉查找树
void destroy_tree(struct bst_node *root)
{
    if (root != NULL)
    {
        destroy_tree(root->left);
        destroy_tree(root->right);
        free(root);
    }
}
