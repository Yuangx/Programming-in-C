//DEV开发环境 ，稀疏矩阵三元组表示
//作者:赵自明
//其中乘法代码参考严蔚敏数据结构
//开发完成日期：07年11月8日
//测试环境:window xp,vista
#include <cstdlib>
#include <iostream>
#define MAXSIZE 100
#define MAXRC 50
using namespace std;
typedef int ElemType;
typedef struct
{
    int i, j;   //非零元在矩阵中的真实位置
    ElemType e; //非零元
} Triple;       //定义存放非零元素的结构体

typedef struct
{
    Triple data[MAXSIZE + 1]; //在使用过程有效位置也是从下标1开始
    int mu, nu, tu;           //行，列，非零元个数
    int rpos[MAXRC + 1];      //从下标为1的位置开始存放每一行的第一个元素对应的在data中的位置
} TSMatrix;                   //定义存放稀疏矩阵的数据类型
int CreateSMatrix(TSMatrix &M)
//创建新的稀疏矩阵
{
    printf("please input m  &  n  & tu:\n");
    scanf("%d,%d,%d", &M.mu, &M.nu, &M.tu);
    while (M.tu > M.mu * M.nu)
    {
        printf("tu must <= mu*nu,input m & n & tu again: \n");
        scanf("%d,%d,%d", &M.mu, &M.nu, &M.tu);
    }

    int k;
    for (k = 1; k <= M.tu; k++)
    {
        printf("the %d number\n", k);
        scanf("%d,%d,%d", &M.data[k].i, &M.data[k].j, &M.data[k].e);
        if (M.data[k].i > M.mu || M.data[k].j > M.nu)
        {
            printf("input error!\n");
            system("PAUSE");
            exit(1);
        }
        while (M.data[k].e == 0)
        {
            printf("elemment  can  not be zero!\n");
            scanf("%d,%d,%d", &M.data[k].i, &M.data[k].j, &M.data[k].e);
        }
    }
    //以下是对寻找每行的第一个非零元在data动态数组中的位置
    int num[MAXRC];
    int t;
    for (t = 1; t <= M.mu; t++)
        num[t] = 0;
    for (t = 1; t <= M.tu; ++t)
        ++num[M.data[t].i];
    M.rpos[1] = 1;
    //求第ran行第一个非零元在Q.data中的位置
    int ran = 1;
    // printf("第%d行的第一个元素在tu中的位置为：%d\n",ran,M.rpos[ran]);
    for (ran = 2; ran <= M.mu; ++ran)
    {
        M.rpos[ran] = M.rpos[ran - 1] + num[ran - 1];
        //printf("第%d行的第一个元素在tu中的位置为：%d\n",ran,M.rpos[ran]);
    }
    //system("PAUSE");
    return 1;
}
int PrintSMatrix(TSMatrix &M)
//以标准格式输出稀疏矩阵
{
    if (!M.tu)
    {
        printf("NULL to Print\n");
        return 0;
    }
    int i, j, k = 1;
    for (i = 1; i <= M.mu; i++)
    {
        for (j = 1; j <= M.nu; j++)
        {
            if (i == M.data[k].i && j == M.data[k].j)
            {
                printf("%d ", M.data[k].e);
                k++;
            }
            else
                printf("# ");
        }
        printf("\n");
    }
    return 1;
}
int                                                                 //此加法算法是对没有rpos算法的改进版本，时间效率更高 为  O(tu)
    AddSMatrix_2(const TSMatrix &M, const TSMatrix &N, TSMatrix &Q) //由于加法结果返回给Q，建议给M,N加上const 防止在操作过程中对M,N修改
{                                                                   //if(Q.data)free(Q.data);//如果data非NULL，释放内存
    //printf("Go into add\n");
    if (M.nu != N.nu || M.mu != N.mu)
    {
        printf("M and N is not compared\n");
        return 0;
    }
    // Q.data=(Triple*)malloc((MAXSIZE+1)*sizeof(Triple));//申请的内存MAXSIZE+1表data 有效位置从1开始，MAXSIZE为最末有效下标
    // if(!Q.data)exit(1);
    Q.mu = M.mu;
    Q.nu = M.nu;
    Q.tu = 0;
    int ran;
    int index_1_begin, index_1_end, index_2_begin, index_2_end;
    int p_1, p_2;
    for (ran = 1; ran <= M.mu; ran++)
    {
        index_1_begin = M.rpos[ran]; //当前行的第一个元素在data 中的位置
        if (ran == M.mu)
            index_1_end = M.tu; //当前行的最后一个元素在data中的位置
        else
            index_1_end = M.rpos[ran + 1] - 1;
        //if(1==index_1_begin-index_1_end)if(1==inde_2_begin-index_2_end)
        index_2_begin = N.rpos[ran];
        if (ran == M.mu)
            index_2_end = N.tu;
        else
            index_2_end = N.rpos[ran + 1] - 1;
        // printf("go into for\n");
        //printf("M当前行的第一个元素位置%d,M当前行的最后一个元素位置%d\n",index_1_begin,index_1_end);
        //printf("N当前行的第一个元素位置%d,M当前行的最后一个元素位置%d\n",index_2_begin, index_2_end);

        for (p_1 = index_1_begin, p_2 = index_2_begin; p_1 <= index_1_end && p_2 <= index_2_end;) //千万不要再在这里加p_1++,p_2++
            if (M.data[p_1].j > N.data[p_2].j)                                                    //对M，N中当前行元素的j下标进行比较
            {                                                                                     // printf("小于\n");
                Q.data[Q.tu + 1].i = N.data[p_2].i;
                Q.data[Q.tu + 1].j = N.data[p_2].j;
                Q.data[Q.tu + 1].e = N.data[p_2].e;
                p_2++;
                Q.tu++;
            }
            else if (M.data[p_1].j < N.data[p_2].j)
            { //printf("小于\n");
                Q.data[Q.tu + 1].i = M.data[p_1].i;
                Q.data[Q.tu + 1].j = M.data[p_1].j;
                Q.data[Q.tu + 1].e = M.data[p_1].e;
                p_1++;
                Q.tu++;
            }
            else if (M.data[p_1].j == N.data[p_2].j)
            { //printf("相等的tu==%d\n",Q.tu+1);
                if (M.data[p_1].e + N.data[p_2].e)
                {
                    Q.data[Q.tu + 1].e = Q.data[Q.tu + 1].e = M.data[p_1].e + N.data[p_2].e;
                    Q.data[Q.tu + 1].i = M.data[p_1].i;
                    Q.data[Q.tu + 1].j = M.data[p_1].j;
                    Q.tu++;
                }
                p_1++;
                p_2++;
            }                                        //for
                                                     //当M或N当前行元素比较完的时候还需要将另一个没有比较完的非零元全部放进Q.data中
        if (p_2 <= index_2_end && p_1 > index_1_end) //在这里注意 比较一定使用<=和>

            while (p_2 <= index_2_end)
            {
                Q.data[Q.tu + 1].i = N.data[p_2].i;
                Q.data[Q.tu + 1].j = N.data[p_2].j;
                Q.data[Q.tu + 1].e = N.data[p_2].e;
                p_2++;
                Q.tu++;
            } //while

        if (p_1 <= index_1_end && p_2 > index_2_end)
            while (p_1 <= index_1_end)
            {
                Q.data[Q.tu + 1].i = M.data[p_1].i;
                Q.data[Q.tu + 1].j = M.data[p_1].j;
                Q.data[Q.tu + 1].e = M.data[p_1].e;
                p_1++;
                Q.tu++;
            } //while
    }         //for
    return 1;
}
int //减法运算与加法运算相似
    SubtMatrix_2(const TSMatrix &M, TSMatrix &N, TSMatrix &Q)
{ //if(Q.data)free(Q.data);//如果data非NULL，释放内存
    //printf("Go into add\n");
    if (M.nu != N.nu || M.mu != N.mu)
    {
        printf("M and N is not compared\n");
        return 0;
    }
    // Q.data=(Triple*)malloc((MAXSIZE+1)*sizeof(Triple));//申请的内存MAXSIZE+1表data 有效位置从1开始，MAXSIZE为最末有效下标
    // if(!Q.data)exit(1);
    for (int i = 1; i <= N.tu; ++i)
        N.data[i].e = -N.data[i].e;
    AddSMatrix_2(M, N, Q);
}
int //没有使用rpos的加法 时间复杂度为O(tu*tu)
    AddSMatrix(const TSMatrix &M, const TSMatrix &N, TSMatrix &Q)
//两个稀疏矩阵相加，结果存放到 Q
{
    //    if(Q.data)free(Q.data);
    if (M.nu != N.nu || M.mu != N.mu)
    {
        printf("M and N is not compared\n");
        return 0;
    }
    //Q.data=(Triple*)malloc((MAXSIZE+1)*sizeof(Triple));
    // if(!Q.data)exit(1);
    Q.mu = M.mu;
    Q.nu = M.nu;
    Q.tu = 0;
    int k, k_1 = 1, k_2 = 1;
    for (k = 1; k_1 <= M.tu && k_2 <= N.tu;)
        if (M.data[k_1].i < N.data[k_2].i)
        {
            Q.data[k].i = M.data[k_1].i;
            Q.data[k].j = M.data[k_1].j;
            Q.data[k].e = M.data[k_1].e;
            Q.tu++;
            k_1++;
            k++;
        }
        else if (M.data[k_1].i > N.data[k_2].i)
        {
            Q.data[k].i = N.data[k_2].i;
            Q.data[k].j = N.data[k_2].j;
            Q.data[k].e = N.data[k_2].e;
            Q.tu++;
            k_2++;
            k++;
        }
        else
        {
            if (M.data[k_1].j < N.data[k_2].j)
            {
                Q.data[k].i = M.data[k_1].i;
                Q.data[k].j = M.data[k_1].j;
                Q.data[k].e = M.data[k_1].e;
                Q.tu++;
                k_1++;
                k++;
            }
            else if (M.data[k_1].j > N.data[k_2].j)
            {
                Q.data[k].i = N.data[k_2].i;
                Q.data[k].j = N.data[k_2].j;
                Q.data[k].e = N.data[k_2].e;
                Q.tu++;
                k_2++;
                k++;
            }
            else
            {
                if (M.data[k_1].e + N.data[k_2].e)
                {
                    Q.data[k].i = M.data[k_1].i;
                    Q.data[k].j = M.data[k_1].j;
                    Q.data[k].e = M.data[k_1].e + N.data[k_2].e;
                    Q.tu++;
                    k_1++;
                    k_2++;
                    k++;
                }
                else
                {
                    k_1++;
                    k_2++;
                }
            }
        }
    if (k_1 > M.tu && k_2 <= N.tu)
    {
        --k_1;
        for (; k_2 <= N.tu; k_2++, k++)
        {
            Q.data[k].i = N.data[k_2].i;
            Q.data[k].j = N.data[k_2].j;
            Q.data[k].e = N.data[k_2].e;
            Q.tu++;
        }
    }
    if (k_1 <= M.tu && k_2 > N.tu)
    {
        --k_2;
        for (; k_1 <= M.tu; k_1++, k++)
        {
            Q.data[k].i = M.data[k_1].i;
            Q.data[k].j = M.data[k_1].j;
            Q.data[k].e = M.data[k_1].e;
            Q.tu++;
        }
    }
    return 1;
}
int SubtMatrix(const TSMatrix &M, const TSMatrix &N, TSMatrix &Q)
//两个稀疏矩阵相减，结果存放到 Q
{
    //  if(Q.data)free(Q.data);
    if (M.nu != N.nu || M.mu != N.mu)
    {
        printf("M and N is not compared\n");
        return 0;
    }
    // Q.data=(Triple*)malloc((MAXSIZE+1)*sizeof(Triple));
    //  if(!Q.data)exit(1);
    Q.mu = M.mu;
    Q.nu = M.nu;
    Q.tu = 0;
    int k, k_1 = 1, k_2 = 1;
    for (k = 1; k_1 <= M.tu && k_2 <= N.tu;)
        if (M.data[k_1].i < N.data[k_2].i)
        {
            Q.data[k].i = M.data[k_1].i;
            Q.data[k].j = M.data[k_1].j;
            Q.data[k].e = M.data[k_1].e;
            Q.tu++;
            k_1++;
            k++;
        }
        else if (M.data[k_1].i > N.data[k_2].i)
        {
            Q.data[k].i = N.data[k_2].i;
            Q.data[k].j = N.data[k_2].j;
            Q.data[k].e = -N.data[k_2].e;
            Q.tu++;
            k_2++;
            k++;
        }
        else
        {
            if (M.data[k_1].j < N.data[k_2].j)
            {
                Q.data[k].i = M.data[k_1].i;
                Q.data[k].j = M.data[k_1].j;
                Q.data[k].e = M.data[k_1].e;
                Q.tu++;
                k_1++;
                k++;
            }
            else if (M.data[k_1].j > N.data[k_2].j)
            {
                Q.data[k].i = N.data[k_2].i;
                Q.data[k].j = N.data[k_2].j;
                Q.data[k].e = -N.data[k_2].e;
                Q.tu++;
                k_2++;
                k++;
            }
            else
            {
                if (M.data[k_1].e - N.data[k_2].e)
                {
                    Q.data[k].i = M.data[k_1].i;
                    Q.data[k].j = M.data[k_1].j;
                    Q.data[k].e = M.data[k_1].e - N.data[k_2].e;
                    Q.tu++;
                    k_1++;
                    k_2++;
                    k++;
                }
                else
                {
                    k_1++;
                    k_2++;
                }
            }
        }
    if (k_1 > M.tu && k_2 <= N.tu)
    {
        --k_1;
        for (; k_2 <= N.tu; k_2++, k++)
        {
            Q.data[k].i = N.data[k_2].i;
            Q.data[k].j = N.data[k_2].j;
            Q.data[k].e = -N.data[k_2].e;
            Q.tu++;
        }
    }
    if (k_1 <= M.tu && k_2 > N.tu)
    {
        --k_2;
        for (; k_1 <= M.tu; k_1++, k++)
        {
            Q.data[k].i = M.data[k_1].i;
            Q.data[k].j = M.data[k_1].j;
            Q.data[k].e = M.data[k_1].e;
            Q.tu++;
        }
    }
    return 1;
}
int MultSMatrix(const TSMatrix &M, const TSMatrix &N, TSMatrix &Q)
//两个稀疏矩阵相乘,由于不改变M，N，结果存放到Q中，所以给M,N参数加CONST限定
{
    if (M.nu != N.mu)
    {
        printf("M.nu!=N.mu\n");
        return 0;
    }
    //system("PAUSE");
    // if(Q.data)free(Q.data);
    //  if( (Q.data=(Triple*)malloc((MAXSIZE+1)*sizeof(Triple)))<0)exit(1);
    Q.mu = M.mu;
    Q.nu = N.nu;
    Q.tu = 0;
    if (M.tu * N.tu)
    {
        int arow;
        int ctemp[N.nu + 1];
        for (arow = 1; arow <= M.mu; ++arow)
        {
            int i;
            for (i = 1; i <= N.nu; i++)
                ctemp[i] = 0;
            Q.rpos[arow] = Q.tu + 1;
            // printf("第%d行Q.RPOS的位置在%d\n",arow,Q.rpos[arow]);
            // system("PAUSE");
            int tp;
            if (arow < M.mu)
                tp = M.rpos[arow + 1];
            else
            {
                tp = M.tu + 1;
            }
            //printf("该次的tp是%d\n",tp);
            //  system("PAUSE");
            int brow, t, ccol, p;
            for (p = M.rpos[arow]; p < tp; ++p)
            {
                brow = M.data[p].j;
                if (brow < N.mu)
                    t = N.rpos[brow + 1];
                else
                {
                    t = N.tu + 1;
                }
                int q;
                for (q = N.rpos[brow]; q < t; ++q)
                {
                    ccol = N.data[q].j;
                    ctemp[ccol] += M.data[p].e * N.data[q].e;
                    //  printf("now ctemp%d==%d\n", ccol,ctemp[ccol]);
                }
            }
            //  for(ccol=1;ccol<=Q.nu;++ccol)printf("ctemp[ccol]==%d\n",ctemp[ccol]);
            for (ccol = 1; ccol <= Q.nu; ++ccol)
                if (ctemp[ccol])
                {
                    if (++Q.tu > MAXSIZE)
                        return 0;
                    //  printf("CTEMP  %d\n",ctemp[ccol]);
                    Q.data[Q.tu].i = arow;
                    Q.data[Q.tu].j = ccol;
                    Q.data[Q.tu].e = ctemp[ccol];
                }
        }
    }
    return 1;
}

int main(int argc, char *argv[])
{

    TSMatrix T;
    TSMatrix W;
    printf("================  稀疏矩阵运算器  ===================\n");
    printf("   please enter: +,-,*,q   (Q,q)to exit program\n%%");
    char c;
    while (1)
    {
        scanf("%c", &c);
        fflush(stdin);
        switch (c)
        {
        case '+':
        {
            TSMatrix M;
            TSMatrix N;
            TSMatrix Q;
            CreateSMatrix(M);
            printf("M smatrix:\n");
            PrintSMatrix(M);
            CreateSMatrix(N);
            printf("N smatrix:\n");
            PrintSMatrix(N);
            AddSMatrix_2(M, N, Q);
            printf("M smatrix add N  smatrix:\n");
            PrintSMatrix(Q);
            fflush(stdin);
            printf("please enter: +,-,*,q   (Q,q)to exit program\n%%");
            break;
        }
        case '-':
        {
            TSMatrix M;
            TSMatrix N;
            TSMatrix Q;
            CreateSMatrix(M);
            printf("M smatrix:\n");
            PrintSMatrix(M);
            CreateSMatrix(N);
            printf("N smatrix:\n");
            PrintSMatrix(N);
            SubtMatrix_2(M, N, Q);
            printf("M smatrix sub N  smatrix:\n");
            PrintSMatrix(Q);
            fflush(stdin);
            printf("   please enter: +,-,*,q   (Q,q)to exit program\n%%");
            break;
        }
        case '*':
        {
            TSMatrix M;
            TSMatrix N;
            TSMatrix Q;
            CreateSMatrix(M);
            printf("M smatrix:\n");
            PrintSMatrix(M);
            CreateSMatrix(N);
            printf("N smatrix:\n");
            PrintSMatrix(N);
            MultSMatrix(M, N, Q);
            printf("M smatrix  mul N smatirx:\n");
            PrintSMatrix(Q);
            fflush(stdin);
            printf("   please enter: +,-,*,q   (Q,q)to exit program\n%%");
            break;
        }
        case 'q':
        case 'Q':
            return EXIT_SUCCESS;
        default:
        {
            printf("input error please enter again\n%%");
            break;
        }
        }
    }
    return 0;
}