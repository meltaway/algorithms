#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <progbase.h>
#include <progbase/console.h>

struct SLNode
{
    int data;
    struct SLNode *next;
};

struct DLNode
{
    int data;
    struct DLNode *next;
    struct DLNode *prev;
};

struct DLNode *createDLNode(int data); 
struct DLNode *addDLNode(struct DLNode *head, struct DLNode *node); 
void printDLList(struct DLNode *list); 
int sizeDL(struct DLNode *list); 
void DLNode_clear(struct DLNode *head);

struct SLNode *createSLNode(int data);
void printSLList(struct SLNode *list); 
int sizeSL(struct SLNode *list); 
void SLNode_clear(struct SLNode *head);

struct DLNode *removeDLNode(struct DLNode *head);
struct SLNode *addSLNode(struct SLNode* head, struct SLNode* node); 
struct SLNode *createSecondList(struct DLNode* dlHead);

struct DLNode *find_Half(struct DLNode *head);
int count_task(struct DLNode *head);
struct SLNode *find_max(struct SLNode *head);

int main()
{
    system("clear");
    struct DLNode *head2 = NULL;
    struct SLNode *head = NULL;
    char key = 0;
    while (1)
    {
        printf("1 - print lists\n2 - addDLNode\n3 - createSecondList\nq - quite\n");
        key = Console_getChar();
        system("clear");
        if (key == '1')
        {
            printDLList(head2);
            printSLList(head);
        }
        if (key == '2')
        {
            int data = 0;
            printf("Enter data of node\n");
            scanf("%i", &data);
            system("clear");
            struct DLNode *new_node = createDLNode(data);
            head2 = addDLNode(head2, new_node);
            printDLList(head2);
        }
        if (key == '3')
        {
            head = createSecondList(head2);
            int c = count_task(head2);
            for (int i = 0; i < c; i++)
            {
                head2 = removeDLNode(head2);
            }
            printDLList(head2);
            printSLList(head);
            SLNode_clear(head);
        }
        if (key == 'q')
        {
            SLNode_clear(head);
            head = NULL;
            DLNode_clear(head2);
            head2 = NULL;
            break;
        }
    }
}

struct DLNode* createDLNode(int data) 
{
    struct DLNode *pnode = malloc(sizeof(struct DLNode));
    pnode->data = data;
    pnode->next = NULL;
    pnode->prev = NULL;
    return pnode;
}

int sizeDL(struct DLNode *node)
{
    int size = 0;
    while (node != NULL)
    {
        size += 1;
        node = node->next;
    }
    return size;
}

struct DLNode *find_Half(struct DLNode *head)
{
    struct DLNode *node = head;
    int half = sizeDL(head) / 2;
    for(int i = 0; i < half; i++)
    {
        node = node->next;
    }
    return node;
}

int count_task(struct DLNode *head)
{
    struct DLNode *node = head;
    int num = 0;
    while(node != NULL)
    {
        if (node->data <= 10 && node->data >= -10) num++;
        node = node->next;
    }
    return num;
}

struct SLNode *find_max(struct SLNode *head)
{
    struct SLNode *max_node = head; 
    struct SLNode *node = head;
    while (node != NULL)
    {
        if (node->data > max_node->data) max_node = node;
        node = node->next;
    }
    return max_node;
}

struct DLNode *addDLNode(struct DLNode *head, struct DLNode *node)
{
    if (head == NULL)
    {
        head = node;
    }
    else 
    {
        struct DLNode *half_node = find_Half(head);
        if (half_node->next == NULL) 
        {
            half_node->next = node;
            node->prev = half_node;
        }
        else 
        {
            node->next = half_node->next;
            half_node->next = node;
            node->prev = half_node;
            node->next->prev = node;
        }
    }
    return head;
}

struct DLNode *removeDLNode(struct DLNode *head)
{
    struct DLNode *node = head;
    struct DLNode *rem_node = NULL;
    while(node != NULL)
    {
        if (node->data <= 10 && node->data >= -10) 
        {
            rem_node = node;
            break;
        }
        node = node->next;
    }
    if (rem_node == NULL) return head; 
    if(rem_node->prev == NULL && rem_node->next == NULL)
    {
        head = rem_node;
        DLNode_clear(head);
        head = NULL;
    } else if(rem_node->prev == NULL && rem_node->next != NULL)
    {
        head = rem_node->next;
        head->prev = NULL;
        free(rem_node);
    }
    else if(rem_node->prev != NULL && rem_node->next != NULL)
    {
        rem_node->prev->next = rem_node->next;
        rem_node->next->prev = rem_node->prev;
        free(rem_node);
    }
    else if(rem_node->prev != NULL && rem_node->next == NULL)
    {
        rem_node->prev->next = NULL;
        free(rem_node);
    }
    return head;
}

struct SLNode *addSLNode(struct SLNode* head, struct SLNode* node)
{
    if(head == NULL) head = node;
    else
    {
        struct SLNode *max = find_max(head); 
        node->next = max->next;
        max->next = node;
    }
    return head;
}
struct SLNode *createSecondList(struct DLNode* dlHead)
{
    struct DLNode *node = dlHead;
    struct SLNode *head = NULL;
    while (node != NULL)
    {
        if (node->data <= 10 && node->data >= -10)
        {
            struct SLNode *new_SLNode = createSLNode(node->data);
            head = addSLNode(head, new_SLNode);
        }
        node = node->next;
    }
    return head;
}

void printDLList(struct DLNode *node)
{
    if (node != NULL)
    {
        printf("Size DLlist - %i\n", sizeDL(node));
        printf("Nods: ");
        while (node != NULL)
        {
            printf("%i -> ", node->data);
            node = node->next;
        }
        puts("\n");
    }
    else
    {
        printf("Size DLlist - 0\n");
        printf("NULL\n");
    }
}

void DLNode_clear(struct DLNode *head)
{
    struct DLNode *node = head;
    while (node != NULL)
    {
        struct DLNode *next = node->next;
        free(node);
        node = next;
    }
}

struct SLNode *createSLNode(int data)
{
    struct SLNode *pnode = malloc(sizeof(struct SLNode));
    pnode->data = data;
    pnode->next = NULL;
    return pnode;
}


int sizeSL(struct SLNode *node)
{
    int size = 0;
    while (node != NULL)
    {
        size += 1;
        node = node->next;
    }
    return size;
}

void printSLList(struct SLNode *node)
{
    puts("-----");
    if (node != NULL)
    {
        printf("Size SLlist - %i\n", sizeSL(node));
        printf("Nods: ");
        while (node != NULL)
        {
            printf("%i -> ", node->data);
            node = node->next;
        }
        puts("\n");
    }
    else
    {
        printf("Size SLlist - 0\n");
        printf("NULL\n");
    }
    puts("");
}

void SLNode_clear(struct SLNode *head)
{
    struct SLNode *node = head;
    while (node != NULL)
    {
        struct SLNode *next = node->next;
        free(node);
        node = next;
    }
}