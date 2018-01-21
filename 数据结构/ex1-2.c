//�Դ���ͷ��㵥����ʵ����ز���
#include <stdio.h>
#include <stdlib.h>


struct node												//��㶨��
{
	int element;
	struct node * link;
};
typedef struct node Node;

void crelink(Node * first,int n);				//��������ͷ��㵥�������ú����������ɷ�
void inslink(Node * first,int pos,int x);		//����ͷ��㵥����posλ�ò���ֵΪx���½��
void dellink(Node * first,int pos);				//ɾ������ͷ��㵥����posλ���ϵĽ��
void prilink(Node * first);						//�������ͷ��㵥�����е�ֵ
Node *findlink(Node *first,int x);				//���Ҵ���ͷ��㵥�������Ƿ����ֵΪx�Ľ��


void main()
{
	Node *first,*p;
	int size,pos1,pos2,x,key;

	first=(Node *)malloc(sizeof(Node));				//���ô��������Ĳ���
	first->link=NULL;
	printf("\n������������������Ľ����:");
	scanf("%d",&size);
	crelink(first,size);	//���ô���
	prilink(first);			//�������

	printf("\n������������λ�úͽ���ֵx:\n");		//���ò��뺯���Ĳ���
	scanf("%d%d",&pos1,&x);
	inslink(first,pos1,x);	//���ò���
	prilink(first);			//�������

	printf("\n������ɾ������λ��:\n");			//����ɾ�������Ĳ���
	scanf("%d",&pos2);
	dellink(first,pos2);	//����ɾ��
	prilink(first);			//�������

	printf("\n����Ҫ���ҵ�key:\n");
	scanf("%d",&key);
	p=findlink(first,key);
	if(p)
		printf("\n���ҳɹ���");
	else
		printf("\n����ʧ�ܣ�");				

}


void crelink(Node * first,int n)					//��������ͷ��㵥�������ú����������ɷ�
{
	int i;
	Node *p,*s;										//pʼ��ָ���βλ�ã�s���ڽ����½��

	p=first;
	printf("\n�����뵥�������ֵ:\n");
	for(i=1;i<=n;i++)
	{
		s=(Node *)malloc(sizeof(Node));				//�����½��
		scanf("%d",&s->element);
		s->link=NULL;
		p->link=s;
		p=s;
	}
}

void inslink(Node * first,int pos,int x)		//����ͷ��㵥����posλ�ò���ֵΪx���½��
{
	int i;
	Node *p,*q;

	p=first;
	i=0;
	while((i<pos-1)&&(p!=NULL))				//pָ������ǰһ�����
	{
		p=p->link;
		i++;
	}
	q=(Node *)malloc(sizeof(Node));			//�����½��
	q->element=x;
	q->link=p->link;		//�������
	p->link=q;
}

void dellink(Node * first,int pos)			//ɾ������ͷ��㵥����posλ���ϵĽ��				
{
	int i;
	Node *p,*q;

	p=first;
	i=0;
	while((i<pos-1)&&(p->link!=NULL))		//pָ������ǰһ�����
	{
		p=p->link;
		i++;
	}
	q=p->link;
	p->link=q->link;		//ɾ������
	free(q);
}

void prilink(Node * first)				//�������ͷ��㵥�����е�ֵ
{
	Node *p;

	printf("\n��ǰ������Ϊ:\n");
	p=first->link;
	while(p)
	{
		printf("%d ",p->element);
		p=p->link;
	}
}

Node *findlink(Node *first,int x)				//���Ҵ���ͷ��㵥�������Ƿ����ֵΪx�Ľ��
{
	Node *p;

	p=first->link;
	while((p->element!=x)&&(p!=NULL))
		p=p->link;
	return p;
}










