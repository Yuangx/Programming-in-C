#include<stdio.h>
#include<stdlib.h>

typedef struct list{
    int data;
    struct list *next;

}list;

void fun(list *head,int a ,int b){
    list *pre,*p;
    pre=head;
    p=pre->next;
    while(p){
        if(p->data>a&&p->data<b){
            pre->next=p->next;
            p=pre->next;
        }
        else{
            pre=pre->next;
            p=pre->next;
        }
    }
}

