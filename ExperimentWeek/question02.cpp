#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void main(){

    int a,m,n,x;
    double t;

    printf("��ѡ��Ҫ���еĲ�����\n");
    printf("1.���ȷֲ�  2.ָ���ֲ�\n");
    scanf("%d",&a);
    if(a==1){
        printf("�����������˵�Ĵ�С(��С���)��\n");
        scanf("%d,%d",&m,&n);
        printf("%d",rand()%(n-m+1)+m);
    }else if(a==2){
        printf("�����������˵�Ĵ�С(��С���)��������ֵ��\n");
        scanf("%d,%d,%f",&m,&n,&t);
        x=rand()%(n-m+1)+m;
        printf("%f",pow(t,x));    //pow(t,x):t��x�η�
    }else{
        printf("��������ȷ����ţ�");
    }
}
