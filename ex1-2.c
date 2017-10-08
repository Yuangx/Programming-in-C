//以带表头结点单链表实现相关操作
#include <stdio.h>
#include <stdlib.h>


struct node												//结点定义
{
	int element;
	struct node * link;
};
typedef struct node Node;

void crelink(Node * first,int n);				//创建带表头结点单链表，采用后置链表生成法
void inslink(Node * first,int pos,int x);		//带表头结点单链表pos位置插入值为x的新结点
void dellink(Node * first,int pos);				//删除带表头结点单链表pos位置上的结点
void prilink(Node * first);						//输出带表头结点单链表中的值
Node *findlink(Node *first,int x);				//查找带表头结点单链表中是否存在值为x的结点


void main()
{
	Node *first,*p;
	int size,pos1,pos2,x,key;

	first=(Node *)malloc(sizeof(Node));				//设置创建函数的参数
	first->link=NULL;
	printf("\n请输入欲创建单链表的结点数:");
	scanf("%d",&size);
	crelink(first,size);	//调用创建
	prilink(first);			//调用输出

	printf("\n请输入插入结点的位置和结点的值x:\n");		//设置插入函数的参数
	scanf("%d%d",&pos1,&x);
	inslink(first,pos1,x);	//调用插入
	prilink(first);			//调用输出

	printf("\n请输入删除结点的位置:\n");			//设置删除函数的参数
	scanf("%d",&pos2);
	dellink(first,pos2);	//调用删除
	prilink(first);			//调用输出

	printf("\n输入要查找的key:\n");
	scanf("%d",&key);
	p=findlink(first,key);
	if(p)
		printf("\n查找成功！");
	else
		printf("\n查找失败！");				

}


void crelink(Node * first,int n)					//创建带表头结点单链表，采用后置链表生成法
{
	int i;
	Node *p,*s;										//p始终指向表尾位置，s用于建立新结点

	p=first;
	printf("\n请输入单链表结点的值:\n");
	for(i=1;i<=n;i++)
	{
		s=(Node *)malloc(sizeof(Node));				//创建新结点
		scanf("%d",&s->element);
		s->link=NULL;
		p->link=s;
		p=s;
	}
}

void inslink(Node * first,int pos,int x)		//带表头结点单链表pos位置插入值为x的新结点
{
	int i;
	Node *p,*q;

	p=first;
	i=0;
	while((i<pos-1)&&(p!=NULL))				//p指向插入点前一个结点
	{
		p=p->link;
		i++;
	}
	q=(Node *)malloc(sizeof(Node));			//创建新结点
	q->element=x;
	q->link=p->link;		//插入过程
	p->link=q;
}

void dellink(Node * first,int pos)			//删除带表头结点单链表pos位置上的结点				
{
	int i;
	Node *p,*q;

	p=first;
	i=0;
	while((i<pos-1)&&(p->link!=NULL))		//p指向插入点前一个结点
	{
		p=p->link;
		i++;
	}
	q=p->link;
	p->link=q->link;		//删除过程
	free(q);
}

void prilink(Node * first)				//输出带表头结点单链表中的值
{
	Node *p;

	printf("\n当前单链表为:\n");
	p=first->link;
	while(p)
	{
		printf("%d ",p->element);
		p=p->link;
	}
}

Node *findlink(Node *first,int x)				//查找带表头结点单链表中是否存在值为x的结点
{
	Node *p;

	p=first->link;
	while((p->element!=x)&&(p!=NULL))
		p=p->link;
	return p;
}










