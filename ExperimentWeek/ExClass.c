#include <stdio.h>
#include<malloc.h>

typedef char T;

typedef struct BinaryTreeNode{
   T Data;
   struct BinaryTreeNode *LChild,*RChild;
}BinaryTree;

BinaryTree *CreateBinaryTree(BinaryTreeNode *T){
  char ch;
  ch=getchar();
  if ( ch = '#' ){
    T = NULL;
  }else{
    T = (BinaryTreeNode *)malloc(sizeof (BinaryTreeNode));
    T -> Data = ch;
    T->LChild = CreateBinaryTree(T -> LChild);
    T->RChild = CreateBinaryTree(T -> RChild);
  }
  return T;
}

void Visit(BinaryTree T) {
  if (T->Data != '#') {
    printf("%c\n",T -> Data );
  }
}

void PreOrder(BinaryTree T){
    if(T!=NULL)
        return;
    printf("%c",T->Data);
    PreOrder(T->LChild);
    PreOrder(T->RChild);
}

void InOrder(BinaryTree T){
    if (T = NULL){
        return ;
}
  InOrder(T -> LChild);
  printf("%c\n", T -> Data );
  InOrder(T -> RChild);
}

void PostOrder(BinaryTree T){
    if (T = NULL){
        return ;
    }
    PostOrder(T -> LChild);
    PostOrder(T -> RChild);
    printf("%c\n", T -> Data );
}

int GetNodeCount(BinaryTree T)  {
    if (T == NULL)
        return 0;
    int LeftNum  =  GetNodeCount(T -> LChild);
    int RightNum =  GetNodeCount(T -> RChild);
    int ret = LeftNum+RightNum+1;
    printf("%d\n", ret );
}

int TreeDepth(BinaryTree T){
      if(!T){
        return 0;
      }
      int Left = TreeDepth(T->LChild);
      int Right = TreeDepth(T->RChild);
      return (Left > Right) ? (Left + 1) : (Right + 1);
}

int getLeafNode(BinaryTree T)  {
    if(NULL == T)
        return 0;
    if(NULL == T->LChild && NULL == T->RChild)
        return 1;
    return getLeafNode(T->LChild) + getLeafNode(T->RChild);
}

void show(BinaryTreeNode T){
    int Nodes,Leaves,Heigth;
    printf("����������£�\n");
    PreOrder(T);
    printf("\n����������£�\n");
    InOrder(T);
    printf("\n����������£�\n");
    PostOrder(T);
    Nodes=GetNodeCount(T);
    printf("�����Ϊ��%d\n",Nodes);
    Leaves=getLeafNode(T);
    printf("Ҷ����Ϊ��%d\n",Leaves);
    Heigth=TreeDepth(T);
    printf("�߶�Ϊ��%d\n",Heigth);
}

int main() {
    BinaryTreeNode *T;
    printf("��������:");
    T=CreateBinaryTree(T);
    Visit(T);
    show(T);

    return 0;
}
