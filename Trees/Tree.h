/*
 * Desc.: Library definition of a binary tree
*/

#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;
struct node
{
    int data;
    Node *left;
    Node *right;
};

Node *new_node(int data);
void inorder(Node *tmp);
void insert(Node *tmp, int key);
#endif
