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

void crelink(Node *first, int n)
{
    int i;
    Node *p, *s;
    p = first;
    printf("\n�����뵥�������ֵ:\n");
    for (i = 1; i <= n; i++)
    {
        s = (Node *)malloc(sizeof(Node));
        scanf("%d", &s->element);
        s->link = NULL;
        p->link = s;
        p = s;
    }
}

void dellink(Node *first, int pos)
{
    int i;
    Node *p, *q;

    p = first;
    i = 0;
    while ((i < pos - 1) && (p->link != NULL))
    {
        p = p->link;
        i++;
    }
    q = p->link;
    p->link = q->link; //ɾ������
    free(q);
}

int Delete (int a, int b,int pos)
{
    int *p;
    if(*p>=a&&*p<=b){
        void dellink(p, pos);
    }else{
        return 0;
    }
}

int main()
{
    Node *first, *p;
    int size, x, y , z;

    first = (Node *)malloc(sizeof(Node));
    first->link = NULL;
    printf("\n������������������Ľ����:");
    scanf("%d", &size);
    crelink(first, size);

    printf("\n������ɾ������λ��:\n"); //����ɾ�������Ĳ���
    scanf("%d", &z);
    dellink(first, z); //����ɾ��
    Delete(x, y, z);


    return 0;
}
