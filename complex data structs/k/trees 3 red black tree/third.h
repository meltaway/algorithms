#pragma once
#include <iostream>
#include <stdlib.h>

using namespace std;

struct Node {
    int color; //1 red, 0 black
    int data;
    struct Node *children[2]; //1 right, 0 left
};

struct Tree {
    struct Node *root;
};

struct Node *createNode(int data);

int isRed(struct Node *root);

struct Node *singleRotate(struct Node *root, int dir);

struct Node *doubleRotate(struct Node *root, int dir);

int checkProperties(struct Node *root);

int insert(struct Tree *tree, int data);

int remove(struct Tree *tree, int data);

void printNode(struct Node *root, char pos, int depth);