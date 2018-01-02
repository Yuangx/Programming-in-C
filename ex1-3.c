#include <stdio.h>
#include <stdlib.h>

struct poly
{
	int coef;
	int exp;
	struct poly *link;
};
typedef struct poly Poly;

void CreatePoly(Poly *p,int n);			//创建一元多项式
void AddPoly(Poly *pa,Poly *pb);		//两个一元多项式相加
void CopyPoly(Poly *p1,Poly *p2);		//一元多项式p1复制到p2中
void MutipliedPoly(Poly *pa,Poly *pb,Poly *pc);	//两个一元多项式相乘
void OutputPoly(Poly *p);				//输出一元多项式
void ClearPoly(Poly *p);				//释放一元多项式

void main()
{
	Poly *pa,*pb,*p1,*p2,*p3;
	int n1,n2;

	pa=(Poly *)malloc(sizeof(Poly));				//建立第一个一元多项式
	pa->link=NULL;
	printf("\n输入第一个一元多项式的长度:\n");
	scanf("%d",&n1);
	CreatePoly(pa,n1);

	pb=(Poly *)malloc(sizeof(Poly));				//建立第二个一元多项式
	pb->link=NULL;
	printf("\n输入第二个一元多项式的长度:\n");
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
	printf("\n两个一元多项式相加的结果为:\n");
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
	printf("\n两个一元多项式相乘的结果为:\n");
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
	printf("\n请输入一元多项式各项的系数和指数:\n");
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

	printf("\n当前一元多项式为:\n");
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



