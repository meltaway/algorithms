#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <progbase/console.h>

struct SLNode {
    int data;
    struct SLNode *next;
};

struct DLNode {
    int data;
    struct DLNode *prev;
    struct DLNode *next;
};

struct DLNode *createDLNode(int data); 
struct SLNode *createSLNode(int data); 
struct DLNode *addDLNode(struct DLNode *head, struct DLNode *node); 
struct SLNode *addSLNode(struct SLNode *head, struct SLNode *node); 
struct SLNode *SLNode_GetBack(struct SLNode *head); 
struct DLNode *findMin(struct DLNode *head); 
void SLNode_Clear(struct SLNode *head); 
struct DLNode *removeDLNode(struct DLNode *head); 
void printSLList(struct SLNode *list); 
void printDLList(struct DLNode *list); 
int sizeSL(struct SLNode *list); 
int sizeDL(struct DLNode *list); 
struct SLNode *createSecondList(struct DLNode *dlHead); 
bool slListEmpty(struct SLNode *head); 
bool dlListEmpty(struct DLNode *head); 

int main() {
    int key = 0;
    while (key != 'q') {
        //struct SLNode *sl = NULL;
        struct DLNode *dl = NULL;
        system("clear");
        printf("1 - task 1\n2 - task 2\nq - quit");
        key = Console_getChar();
        system("clear");
        if (key == '1') {
            key = 0;
            //struct DLNode *dl = NULL;
            while (1) {
                printf("1 - add DL node after minimum\n2 - print list\nq - quit to task menu\n");
                key = Console_getChar();
                system("clear");

                if (key == '1') {
                    int num = 0;
                    printf("Enter node data (integer): ");
                    scanf("%d", &num);

                    struct DLNode *newNode = createDLNode(num);
                    dl = addDLNode(dl, newNode);
                    printDLList(dl);
                }
                else if (key == '2')
                    printDLList(dl);
                else if (key == 'q') {
                    key = 0;
                    break;
                }
            }
        }
        else if (key == '2') {
            key = 0;
            struct SLNode *sl = NULL;
            while (1) {
                printf("1 - delete nodes (even indices)\n2 - add node\n3 - print DL list\n4 - print SL list\nq - quit to task menu\n");
                key = Console_getChar();
                system("clear");

                if(key == '1') {
                    SLNode_Clear(sl);
                    if (sizeDL(dl) == 1) printf("No even indeces to be deleted.\n\n");
                    else {
                        sl = createSecondList(dl);
                        dl = removeDLNode(dl);
                    }
                    printDLList(dl);
                    printSLList(sl);
                }
                else if(key == '2') {
                    int num = 0;
                    printf("Enter node data (integer): ");
                    scanf("%d", &num);
                    struct SLNode *newnode = createSLNode(num);
                    sl = addSLNode(sl, newnode);
                    printSLList(sl);
                }
                else if (key == '3')
                    printDLList(dl);
                else if (key == '4')
                    printSLList(sl);
                else if (key == 'q') {
                    key = 0;
                    break;
                }
            }
        }
    }
}

struct DLNode *createDLNode(int data) {
    struct DLNode *node = malloc(sizeof(struct DLNode));
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

struct SLNode *createSLNode(int data) {
    struct SLNode *node = malloc(sizeof(struct SLNode));
    node->data = data;
    node->next = NULL;
    return node;
}

struct DLNode *addDLNode(struct DLNode *head, struct DLNode *node) {
    if (dlListEmpty(head)) {
        head = node;
        return head;
    }
    else {
        struct DLNode *min = findMin(head);
        if (!min->next) {
            min->next = node;
            node->prev = min;
        }
        else {
            node->next = min->next;
            min->next->prev = node;
            min->next = node;
            node->prev = min;
        }
    }
    return head;
}

struct SLNode *addSLNode(struct SLNode *head, struct SLNode *node) {
    struct SLNode *tail = SLNode_GetBack(head);
    tail->next = node;
    return head;
}

struct SLNode *SLNode_GetBack(struct SLNode *head) {
    if (!head) return NULL;

    struct SLNode *node = head;
    while (node->next) node = node->next;
    return node;
}

struct DLNode *findMin(struct DLNode *head) {
    struct DLNode *ptr = head;
    struct DLNode *min = head;
    int flag = 1;

    while (ptr) {
        if(flag) {
            min = ptr;
            flag = 0;
        }
        else if (min->data >= ptr->data) min = ptr;
        ptr = ptr->next;
    }
    return min;
}

void SLNode_Clear(struct SLNode *head) {
    struct SLNode *node = head;
    while (node) {
        struct SLNode *next = node->next;
        free(node);
        node = next;
    }
}

struct DLNode *removeDLNode(struct DLNode *head) {
    int size = sizeDL(head);
    struct DLNode *node = head;
    for (int i = 1; i <= size; i++) {
        if (i % 2 == 0) {
            if (!node->next) {
                node->prev->next = NULL;
                free(node);
            }
            else {
                node->prev->next = node->next;
                node->next->prev = node->prev;
                free(node);
            }
        }
        if(node) node = node->next;
    }
    return head;
}

void printSLList(struct SLNode *list) {
    if (slListEmpty(list)) printf("Singly-linked list is empty.\n");
    else {
        struct SLNode *node = list;
        printf("Size: %d\n", sizeSL(node));
        while (node) {
            printf("(%d) -> ", node->data);
            node = node->next;
        }
    }
    puts("\n");
}

void printDLList(struct DLNode *list) {
    if (dlListEmpty(list)) printf("Doubly-linked list is empty.\n");
    else {
        struct DLNode *node = list;
        printf("Size: %d\n", sizeDL(node));
        while (node) {
            if (!node->prev) printf("NULL <- (%d) <->", node->data);
            else if (!node->next) printf(" (%d) -> NULL", node->data);
            else printf(" (%d) <->", node->data);
            node = node->next;
        }
    }
    puts("\n");
}

int sizeSL(struct SLNode *list) {
    struct SLNode *node = list;
    int size = 0;
    while (node) {
        size++;
        node = node->next;
    }
    return size;
}

int sizeDL(struct DLNode *list) {
    struct DLNode *node = list;
    int size = 0;
    while (node) {
        size++;
        node = node->next;
    }
    return size;
}

struct SLNode *createSecondList(struct DLNode *dlHead) {
    int size = sizeDL(dlHead);
    struct DLNode *node = dlHead;
    struct SLNode *head = NULL;
    for (int i = 1; i <= size; i++) {
        if (i % 2 == 0) {
            struct SLNode *newnode = createSLNode(node->data);
            if (!head) head = newnode;            
            else head = addSLNode(head, newnode);
        }
        if (node) node = node->next;
    }
    return head;
}

bool slListEmpty(struct SLNode *head) {
    if (!head) return 1;
    else return 0;
}

bool dlListEmpty(struct DLNode *head) {
    if (!head) return 1;
    else return 0;
}