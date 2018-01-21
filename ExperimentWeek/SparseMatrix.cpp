#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;


 void ShowTable(){
    cout<<"-------------请选择转换的方式------------"<<endl;
    cout<<"-----简明表示法转向传统表示法请输入1-----"<<endl;
    cout<<"-----传统表示法转向简明表示法请输入2-----"<<endl;
    cout<<endl;
}

void ErrorTips(){
    cout<<"-----------------------------------------"<<endl;
    cout<<"------选择错误请正确的选择转换方式-------"<<endl;
    cout<<"-----------------------------------------"<<endl;
    cout<<endl;
}

void TradToSimp(){
    int n,m;
    int i,j;
    int cou = 0;

    cout<<"请输入你所要转换的矩阵的行列值n.m"<<endl;
    cin>>n>>m;
    cout<<"数组的维度为："<<n<<"*"<<m<<endl;

    int **a;
    a=new int*[n];
    for(i=0;i<n;i++)
        a[i]=new int[m];

    ifstream fin("TraMatrix.txt");
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            fin>>a[i][j];
    fin.close();

    ofstream out("OutPutSimp.txt");
    out<<i<<" "<<j;
    for(i = 0; i <n; i ++){
            for(j = 0; j <m; j ++){
                if(a[i][j] != 0){
                    cou++;
                }
            }
     }
    out <<endl;
    out<<cou<<endl;
    cout<<"非零项个数为："<<cou<<endl;
    for(i=0;i<n;i++,cout<<endl)
        for(j=0;j<m;j++)
            cout<<a[i][j]<<" ";

    for(i = 0; i <n; i ++){
            for(j = 0; j <m; j ++){
                if(a[i][j] != 0){
                    out<<i<<" "<<j<<" "<<a[i][j]<<" ";
                }
            }
            out << endl;
     }
        for(i=0;i<n;i++)
      delete []a[i];
     delete []a;
}

void SimpToTrad(){
    int n = 100,m = 3;
    int i,j;
    int x = 0,y = 0;
    int q,w;
    int b[100][100];

    int **a;
    a=new int*[n];
    for(i=0;i<n;i++)
        a[i]=new int[m];

    ifstream ifs("SimpMatrix.txt",ios::in);
    string buf;
    while (ifs){
        if (getline(ifs,buf)){
            cout<<buf<<endl;
        }
    }

    ifstream fin("SimpMatrix.txt");
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            fin>>a[i][j];
    fin.close();

    ofstream out("OutPutTra.txt");
    for(i=1;i <= a[0][0];i++){
        if(x==a[i][0]&&y==a[i][1]){
            b[x][y] = a[i][2];
            x++;
            y++;
        }else{
            b[x][y] = 0;
            x++;
            y++;
        }
    }
    for(q=0;q<x;q++){
        for(w=0;w<y;w++)
            out<<b[q][w]<<" ";
        out<<endl;
    }

    for(q=0;q<x;q++){
        for(w=0;w<y;w++)
            cout<<b[q][w]<<" ";
        cout<<endl;
    }

        for(i=0;i<n;i++)
      delete []a[i];
     delete []a;
}


void MainPage(){
    int choose;
    ShowTable();
    cin >>choose;

    if(choose == 1){
        SimpToTrad();
    }else if(choose == 2){
        TradToSimp();
    }else{
        ErrorTips();
        MainPage();
    }
}


int main(){
    cout<<"----------欢迎使用表示法转换工具---------"<<endl;
    cout<<endl;

    MainPage();

    return 0;
}
