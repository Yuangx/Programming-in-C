#include <stdio.h>
#include <stdlib.h>

#define MAXNUM 20

struct node 
{
    int element;
    struct node *link;
};
typedef struct node Node;

struct linklist
{
    int list[MAXNUM];
    int last;
};
typedef struct linklist link;

oid crelink(Node *first, int n)
{
    int i;
    Node *p, *s; 
    p = first;
    printf("\n请输入单链表结点的值:\n");
    for (i = 1; i <= n; i++)
    {
        s = (Node *)malloc(sizeof(Node)); 
        scanf("%d", &s->element);
        s->link = NULL;
        p->link = s;
        p = s;
    }
}

void DeleteX(pNode *phead)
{
    if (NULL != *phead)
    {
        pNode pDelete = *phead;
        *phead = (*phead)->next;
        delete pDelete;
        pDelete = nullptr;
    }
}

int Delete(linklist, int a, int b)
{
    Node *p, *q;
    p = L;
    while (p->next != NULL)
        p = p->next;
    if (a >= b || L->next->data >= b || a + 1 = b)
    {
        printf("ERROR");
        return ERROR;
    }
    else
    {
        while (p->next->data <= a)
            p = p->next;
        q = p->next;
        while (q->data < b && q != NULL)
        {
            p->next = q->next;
            free(q);
            q = p->next;
        }
        return OK;
    }
}

int main()
{
    link list;
    Node *first, *p;
    int size, x, y;

    first = (Node *)malloc(sizeof(Node)); 
    first->link = NULL;
    printf("\n请输入欲创建单链表的结点数:");
    scanf("%d", &size);
    crelink(first, size); 
    Delete(list, x, y);
    DeleteX(first);

    return 0;
}