#include "third.h"

int isRed(struct Node *root) {
    return root && root->color;
}

struct Node *createNode(int data) {
    struct Node *newNode = (struct Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = 1;
    newNode->children[0] = nullptr;
    newNode->children[1] = nullptr;
    return newNode;
}

struct Node *singleRotate(struct Node *root, int dir) {
    struct Node *save = root->children[!dir];
    root->children[!dir] = save->children[dir];
    save->children[dir] = root;
    root->color = 1;
    save->color = 0;
    return save;
}

struct Node *doubleRotate(struct Node *root, int dir) {
    root->children[!dir] = singleRotate(root->children[!dir], !dir);
    return singleRotate(root, dir);
}

int checkProperties(struct Node *root) {
    int leftTree, rightTree;

    if (!root)
        return 1;
    else {
        struct Node *leftChild = root->children[0];
        struct Node *rightChild = root->children[1];

        if (isRed(root)) //consecutive colors
            if (isRed(leftChild) || isRed(rightChild)) {
                cout << "Red violation" << endl;
                return 0;
            }

        leftTree = checkProperties(leftChild);
        rightTree = checkProperties(rightChild);

        //invalid bst
        if ((leftChild && leftChild->data >= root->data) || (rightChild && rightChild->data <= root->data)) {
            cout << "Binary tree violation" << endl;
            return 0;
        }

        if (leftTree != 0 && rightTree != 0 && leftTree != rightTree) { //invalid black height 
            cout << "Black violation" << endl;
            return 0;
        }

        if (leftTree != 0 && rightTree != 0) //count links to black nodes
            return isRed(root) ? leftTree : leftTree + 1;
        else
            return 0;
    }
}

int insert(struct Tree *tree, int data) {
    if (!tree->root) { //empty tree
        Node * newNode = createNode(data);
        tree->root = newNode;
        if (!tree->root)
            return 0;
    }
    else {
        struct Node head = {}; //dummy root
        struct Node *g, *top; //grandparent and parent
        struct Node *p, *cur; //parent and current node (pointer to insert place)
        int dir = 0, last;

        top = &head;
        g = p = nullptr;
        cur = top->children[1] = tree->root;

        while(1) {
            if (!cur) { //insert as leaf at bottom
                p->children[dir] = cur = createNode(data);
                if (!cur)
                    return 0;
            }
            else if (isRed(cur->children[0]) && isRed(cur->children[1])) { //color flip if both children are red
                printf("Flipping colors for node %d and its children %d, %d\n", cur->data, cur->children[0]->data, cur->children[1]->data);
                cur->color = 1;
                cur->children[0]->color = 0;
                cur->children[1]->color = 0;
            }

            if (isRed(cur) && isRed(p)) { //color violation
                int dir2 = top->children[1] == g;
                if (cur == p->children[last]) {
                    if (!last) printf("Rotating node %d right\n", g->data);
                    else printf("Rotating node %d left\n", g->data);
                    top->children[dir2] = singleRotate(g, !last);
                }
                else {
                    if (!last) printf("Rotating node %d TWICE right\n", g->data);
                    else printf("Rotating node %d TWICE left\n", g->data);
                    top->children[dir2] = doubleRotate(g, !last);
                }
            }

            if (cur->data == data) //found
                break;

            last = dir;
            dir = cur->data < data;

            //move helper pointers one level down
            if (g)
                top = g;
            g = p, p = cur;
            cur = cur->children[dir];
        }
        tree->root = head.children[1]; //update root
    }
    tree->root->color = 0; //make root black
    return 1;
}

int remove(struct Tree *tree, int data) {
    if (tree->root) {
        struct Node head = {}; 
        struct Node *cur, *p, *g; 
        struct Node *found = nullptr;  
        int dir = 1; //start with right subtree

        cur = &head;
        g = p = nullptr;
        cur->children[1] = tree->root;

        while (cur->children[dir]) {
            int last = dir;

            //move one level down
            g = p, p = cur;
            cur = cur->children[dir];
            dir = cur->data < data;

            if (cur->data == data)
                found = cur;

            if (!isRed(cur) && !isRed(cur->children[dir])) { //push red node down
                if (isRed(cur->children[!dir]))
                    p = p->children[last] = singleRotate(cur, dir);
                else if (!isRed(cur->children[!dir])) {
                    struct Node *sibling = p->children[!last];

                    if (sibling) {
                        if (!isRed(sibling->children[!last]) && !isRed(sibling->children[last])) { //color flip
                            printf("Flipping colors for node %d and its children %d, %d\n", p->data, sibling->data, cur->data);
                            p->color = 0;
                            sibling->color = 1;
                            cur->color = 1;
                        }
                        else {
                            int dir2 = g->children[1] == p;

                            if (isRed(sibling->children[last])) {
                                if (last) printf("Rotating node %d right\n", p->data);
                                else printf("Rotating node %d left\n", p->data);
                                g->children[dir2] = doubleRotate(p, last);
                            }
                            else if (isRed(sibling->children[!last])) {
                                if (last) printf("Rotating node %d TWICE right\n", p->data);
                                else printf("Rotating node %d TWICE left\n", p->data);
                                g->children[dir2] = singleRotate(p, last);
                            }

                            //make sure colors are correct
                            cur->color = g->children[dir2]->color = 1;
                            g->children[dir2]->children[0]->color = 0;
                            g->children[dir2]->children[1]->color = 0;
                        }
                    }
                }
            }
        }

        if (found) { //replace and remove
            found->data = cur->data;
            p->children[p->children[1] == cur] = cur->children[cur->children[0] == nullptr];
            free(cur);
        }

        tree->root = head.children[1];
        if (tree->root)
            tree->root->color = 0;
    }
    return 1;
}

void printNode(struct Node *root, char pos, int depth) {
    if(root == NULL)
        return;
    printNode(root->children[1], 'R', depth + 1);

    for (int i = 0; i < depth; i++) 
        cout << "    ";

    if(depth == 0)
        printf("\x1b[30m%s\x1b[0m","ROOT");
    else
        printf("     ");

    if(root->color == 0)
        printf("\x1b[30m%c: \x1b[0m",pos);
    else
        printf("\x1b[31m%c: \x1b[0m",pos);
    
    cout << root->data << endl;

    printNode(root->children[0], 'L', depth+1); 
}