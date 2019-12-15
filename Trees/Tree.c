/*
 * Desc.: Library implementation of a binary tree
*/

#include "Tree.h"

Node *
new_node(int data)
{
    Node *node = (Node *)malloc(sizeof(Node));

    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void
inorder(Node *tmp)
{
    if (!tmp)
        return;

    inorder(tmp->left);
    printf("%d ", tmp->data);
    inorder(tmp->right);
}

void
insert(struct Node *tmp, int key)
{
    
}
