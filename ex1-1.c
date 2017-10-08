#include <stdio.h>
#include <stdlib.h>

#define MAXNUM 20

struct seqlist				
{
	int list[MAXNUM];
	int last;
};
typedef struct seqlist seqtype;

void CreateSeqlist(seqtype *seq,int n);
void InsertSeqlist(seqtype *seq,int pos1,int x);
void DeleteSeqlist(seqtype *seq,int pos2);
void OutputSeqlist(seqtype *seq);
int Findseqlist(seqtype *seq,int k);


void main()
{
	seqtype *seq;
	int n,pos1,x,pos2,k,loc;

	seq=(seqtype *)malloc(sizeof(seqtype));
	seq->last=0;
	printf("\n����˳����ʵ�ʳ���:\n");
	scanf("%d",&n);
	CreateSeqlist(seq,n);
	OutputSeqlist(seq);

	printf("\n��������Ͳ����ֵ:\n");
	scanf("%d%d",&pos1,&x);
	InsertSeqlist(seq,pos1,x);
	OutputSeqlist(seq);

	printf("\n����ɾ����:\n");
	scanf("%d",&pos2);
	DeleteSeqlist(seq,pos2);
	OutputSeqlist(seq);

	printf("\n������Ҫ���ҵ�����Ԫ��:\n");
	scanf("%d",&k);
	loc=Findseqlist(seq,k);
	if(loc==0)
		printf("\n����ʧ��");
	else
		printf("\n���ҳɹ�");

	free(seq);
}


void CreateSeqlist(seqtype *seq,int n)
{
	int i;

	printf("\n����˳����е�����Ԫ��:\n");
	for(i=1;i<=n;i++)
	{
		scanf("%d",&seq->list[i]);
		seq->last++;
	}
}

void InsertSeqlist(seqtype *seq,int pos1,int x)
{
	int i;

	if(pos1<1||pos1>seq->last+1)
		printf("\n�����Ƿ�������ʧ��\n");
    else if(seq->last==MAXNUM)
		     printf("\n�����������ʧ��\n");
	else
	{
		for(i=seq->last;i>=pos1;i--)
			seq->list[i+1]=seq->list[i];
		seq->list[pos1]=x;
		seq->last++;
	}
}


void DeleteSeqlist(seqtype *seq,int pos2)
{
	int i;

	if(pos2<0||pos2>seq->last)
		printf("\nɾ����Ƿ���ɾ��ʧ��\n");
	else
	{
		for(i=pos2+1;i<=seq->last;i++)
			seq->list[i-1]=seq->list[i];
		seq->last--;
	}
}

void OutputSeqlist(seqtype *seq)
{
	int i;

	printf("\n��ǰ˳���Ϊ:\n");
	for(i=1;i<=seq->last;i++)
		printf("%d ",seq->list[i]);
}


int Findseqlist(seqtype *seq,int k)
{
	int i;

	i=1;
	seq->list[seq->last+1]=k;				//�����ڱ�
	while(seq->list[i]!=k)
		i++;
	if(i<=seq->last)
		return i;
	else
		return 0;
}


