#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void main(){

    int a,m,n,x;
    double t;

    printf("请选择要进行的操作！\n");
    printf("1.均匀分布  2.指数分布\n");
    scanf("%d",&a);
    if(a==1){
        printf("请输入俩个端点的大小(先小后大)：\n");
        scanf("%d,%d",&m,&n);
        printf("%d",rand()%(n-m+1)+m);
    }else if(a==2){
        printf("请输入俩个端点的大小(先小后大)及底数的值：\n");
        scanf("%d,%d,%f",&m,&n,&t);
        x=rand()%(n-m+1)+m;
        printf("%f",pow(t,x));    //pow(t,x):t的x次方
    }else{
        printf("请输入正确的序号！");
    }
}
