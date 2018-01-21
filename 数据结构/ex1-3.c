#include <stdio.h>
#include <stdlib.h>

struct poly
{
	int coef;
	int exp;
	struct poly *link;
};
typedef struct poly Poly;

void CreatePoly(Poly *p,int n);			//����һԪ����ʽ
void AddPoly(Poly *pa,Poly *pb);		//����һԪ����ʽ���
void CopyPoly(Poly *p1,Poly *p2);		//һԪ����ʽp1���Ƶ�p2��
void MutipliedPoly(Poly *pa,Poly *pb,Poly *pc);	//����һԪ����ʽ���
void OutputPoly(Poly *p);				//���һԪ����ʽ
void ClearPoly(Poly *p);				//�ͷ�һԪ����ʽ

void main()
{
	Poly *pa,*pb,*p1,*p2,*p3;
	int n1,n2;

	pa=(Poly *)malloc(sizeof(Poly));				//������һ��һԪ����ʽ
	pa->link=NULL;
	printf("\n�����һ��һԪ����ʽ�ĳ���:\n");
	scanf("%d",&n1);
	CreatePoly(pa,n1);

	pb=(Poly *)malloc(sizeof(Poly));				//�����ڶ���һԪ����ʽ
	pb->link=NULL;
	printf("\n����ڶ���һԪ����ʽ�ĳ���:\n");
	scanf("%d",&n2);
	CreatePoly(pb,n2);

	OutputPoly(pa);
	OutputPoly(pb);

	p1=(Poly *)malloc(sizeof(Poly));
	p1->link=NULL;
	p2=(Poly *)malloc(sizeof(Poly));
	p2->link=NULL;
	CopyPoly(pa,p1);
	CopyPoly(pb,p2);

	AddPoly(p1,p2);
	printf("\n����һԪ����ʽ��ӵĽ��Ϊ:\n");
	OutputPoly(p1);
	ClearPoly(p1);
	ClearPoly(p2);

	p1=(Poly *)malloc(sizeof(Poly));
	p1->link=NULL;
	p2=(Poly *)malloc(sizeof(Poly));
	p2->link=NULL;
	CopyPoly(pa,p1);
	CopyPoly(pb,p2);
	p3=(Poly *)malloc(sizeof(Poly));
	p3->link=NULL;

	MutipliedPoly(p1,p2,p3);
	printf("\n����һԪ����ʽ��˵Ľ��Ϊ:\n");
	OutputPoly(p3);
	ClearPoly(p1);
	ClearPoly(p2);
	ClearPoly(p3);

	ClearPoly(pa);
	ClearPoly(pb);

}


void CreatePoly(Poly *p,int n)
{
	int i;
	Poly *q,*s;

	q=p;
	printf("\n������һԪ����ʽ�����ϵ����ָ��:\n");
	for(i=1;i<=n;i++)
	{
		s=(Poly *)malloc(sizeof(Poly));
		scanf("%d%d",&s->coef,&s->exp);
		s->link=NULL;
		q->link=s;
		q=s;
	}
}

void AddPoly(Poly *pa,Poly *pb)
{
	Poly *p,*q,*pre,*u;
	int x;

	p=pa->link;
	q=pb->link;
	pre=pa;

	while(p&&q)
	{
		if(p->exp<q->exp)
		{
			p=p->link;
			pre=pre->link;
		}
		else if(p->exp>q->exp)
		{
			u=q->link;
			q->link=p;
			pre->link=q;
			pre=q;
			q=u;
		}
		else
		{
			x=p->coef+q->coef;
			if(x!=0)
				p->coef=x;
			else
			{
				pre->link=p->link;
				free(p);
				p=pre->link;
			}
			u=q->link;
			free(q);
			q=u;
		}
	}
	if(q)
		pre->link=q;
	pb->link=NULL;
}

void CopyPoly(Poly *p1,Poly *p2)
{
	Poly *p,*q,*s;

	p=p1->link;
	q=p2;

	while(p)
	{
		s=(Poly *)malloc(sizeof(Poly));
		s->coef=p->coef;
		s->exp=p->exp;
		s->link=NULL;
		q->link=s;
		q=s;
		p=p->link;
	}
}

void MutipliedPoly(Poly *pa,Poly *pb,Poly *pc)
{
	Poly *p,*q,*pd;

	pd=(Poly *)malloc(sizeof(Poly));
	pd->link=NULL;

	p=pa->link;
	while(p)
	{
		CopyPoly(pb,pd);
		q=pd->link;
	    while(q)
		{
			q->coef=q->coef*p->coef;
			q->exp=q->exp+p->exp;
			q=q->link;
		}
		AddPoly(pc,pd);
		p=p->link;
	}

	ClearPoly(pd);
}


void OutputPoly(Poly *p)
{
	Poly *q;

	printf("\n��ǰһԪ����ʽΪ:\n");
	q=p->link;
	while(q)
	{
		printf("%d,%d  ",q->coef,q->exp);
		q=q->link;
	}
}


void ClearPoly(Poly *p)
{
	Poly *q,*u;

	q=p->link;
	while(q)
	{
		u=q->link;
		free(q);
		q=u;
	}
	free(p);
}



