#include<stdio.h>
//#include<malloc.h>

typedef char ElemType;

typedef struct BinaryTreeNode {
    ElemType Data;
    struct BinaryTreeNode *LChild,*RChild;
}BinTree;

BinTree * PreCreate(BinTree *t) {
    char ch;

    ch = getchar();
    if (ch== '#' )
        t=NULL;
    else {
        t=( BinTree * )malloc(sizeof(BinTree));
        t->Data=ch;
        t->LChild = PreCreate( t->LChild );
        t->RChild = PreCreate( t->RChild );
    }
    return t;
}
// 先序遍历
void PreOrderTransverse( BinTree *t ){
    if (t==NULL)
        return;
    printf("%c",t->Data);
    PreOrderTransverse(t->LChild);
    PreOrderTransverse(t->RChild);
}
//中序遍历
void InOrderTransverse(BinTree *t){
    if (t==NULL)
        return;
    InOrderTransverse(t->LChild);
    printf("%c",t->Data);
    InOrderTransverse(t->RChild);
}
//后续遍历
void PosOrderTransverse(BinTree *t){
    if (t==NULL)
        return;
    PosOrderTransverse(t->LChild);
    PosOrderTransverse(t->RChild);
    printf("%c",t->Data);
}
//求结点数
int GetNode(BinTree *t){
    if (t==NULL)
        return 0;
    else
        return 1+GetNode(t->LChild)+GetNode(t->RChild);
}

int GetLeaves(BinTree *t){
    if (t==NULL)
        return 0;
    else if(t->LChild==NULL&&t->RChild==NULL)
        return 1;
    else
        return GetLeaves(t->LChild)+GetLeaves(t->RChild);
}

int GetHeight(BinTree *t){
    int Left,Right;
    if(t == NULL){
        return 0;
    }
    else{
        Left = GetHeight(t->LChild);
        Right= GetHeight(t->RChild);
        return (Left>Right?Left:Right)+1;
    }
}

BinTree *exchange(BinTree *t)
{
    if(t!=NULL)
    if(t->LChild!=NULL||t->RChild!=NULL)
    {
        BinTree *p,*q;
        p = exchange(t->LChild);
        q = exchange(t->RChild);
        t->LChild = q;
        t->RChild = p;
    }
    return t;
}

void show(BinTree *t){
    int Nodes,Leaves,Heigth;
    printf("先序遍历：\n");
    PreOrderTransverse(t);
    printf("\n中序遍历：\n");
    InOrderTransverse(t);
    printf("\n后序遍历：\n");
    PosOrderTransverse(t);
    Nodes=GetNode(t);
    printf("结点数为：%d\n",Nodes);
    Leaves=GetLeaves(t);
    printf("叶子数为：%d\n",Leaves);
    Heigth=GetHeight(t);
    printf("高度为：%d\n",Heigth);
}

int main(){
    BinTree *Tree;
    printf("请输入二叉树的创建\n");
    Tree=PreCreate(Tree);
    show(Tree);
    printf("\n交换左右子树后：\n");
    Tree=exchange(Tree);
    show(Tree);
    return 0;
}
