#include<iostream>
#include<io.h>
#include<cstdio>
#include<time.h>
//对文件操作
#include<Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#include<string>
#include<dos.h>
#include<stdlib.h>
#include<vector>
#include<windows.h>
#include <sys/stat.h>
#include<string>

#define BUFSIZE 1024

using namespace std;

void _file();
void showmenu();
void _desk();
void _setrole();
void _clearrole();
void _enter();
void putDrivesFreeSpace(const char* lpRootPathName);
void putDrivesType(const char* lpRootPathName);
BOOL GetDirverInfo(LPSTR szDrive);

string s1="";

int main()
{
    showmenu();
    return 0;
}

void _file()
{
    string s;

    struct _stat buf;
    int result;

    printf("请输入欲查询的目录：");
    cin>>s;
    s=s1+s;
    _enter();
    long handle;//用于查找句柄
    struct _finddata_t fileinfo;//文件信息的结构体
    while(s.empty() || _access(s.c_str(), 0) != 0)
    {
        printf("空路径，按回车键确认返回主菜单！\n");
        _enter();
        showmenu();
        return;
    }

    const char* to_search= s.data();
    result = _stat( to_search, &buf );
    handle=_findfirst(to_search,&fileinfo);//第一次查找
    if(-1==handle)
    {
        printf("查询不到该文件，按回车键确认返回主菜单！\n");
        _enter();
        showmenu();
        return;
    }
    if(_S_IFREG & buf.st_mode)
    {
        printf("输入为文件，文件名为： ");
        printf("%s\n",fileinfo.name);//打印出第一个文件名
        printf("文件大小为： ");
        printf("%d 字节\n",fileinfo.size);
        printf("创建日期为： ");
        printf("%s\n",asctime(localtime(&fileinfo.time_create)));
        printf("最后一次编辑日期为： ");
        printf("%s\n",asctime(localtime(&fileinfo.time_write)));
        printf("最后一次访问日期为： ");
        printf("%s\n",asctime(localtime(&fileinfo.time_access)));
        _findclose(handle);//别忘了关闭句柄
        printf("已查询完所查文件，按回车键确认返回主菜单！\n");
        _enter();
        showmenu();
    }
    else if(_S_IFDIR & buf.st_mode)
    {
        printf("输入为文件夹，文件夹名为： ");
        printf("%s\n",fileinfo.name);//打印出第一个文件名
        printf("创建日期为： ");
        printf("%s\n",asctime(localtime(&fileinfo.time_create)));
        printf("最后一次编辑日期为： ");
        printf("%s\n",asctime(localtime(&fileinfo.time_write)));
        printf("最后一次访问日期为： ");
        printf("%s\n",asctime(localtime(&fileinfo.time_access)));
        printf("该文件夹包含以下内容：\n");
        int nRet= (handle <0 ) ? -1 : 1;

        string st = s + "\\*.*";

        const char* to_search2= st.data();
        long handle2;
        int x=0,y=0;

        handle2 = _findfirst(to_search2,&fileinfo);
        while ( nRet >= 0 )
        {
            if ( fileinfo.attrib == _A_SUBDIR )   // 如果是目录
            {
                printf("   [%s]*\n", fileinfo.name );
                x++;
            }
            else
            {
                printf("   [%s]\n", fileinfo.name );
                y++;
            }
            nRet = _findnext( handle2, &fileinfo );
        }
        printf("路径下共有 %d 个项目，其中%d 个文件夹，%d 个文件。\n",x+y,x,y);

        _findclose(handle);//别忘了关闭句柄
        printf("已查询完所有文件，按回车键确认返回主菜单！\n");
        _enter();
        showmenu();
    }
}

void showmenu()
{
    printf("----------------欢迎使用本次服务----------------\n");
    printf("\t1  查询文件/文件夹信息\n");
    printf("\t2  查询磁盘信息\n");
    printf("\t3  设置相对路径\n");
    printf("\t4  清除相对路径\n");
    printf("\t5  退出程序\n");
    printf("请输入序号选择菜单：");
    int x;
    cin>>x;
    printf("\n");
    switch(x)
    {
        case 1:
            _file();
            break;
        case 2:
            _desk();
            break;
        case 3:
            _setrole();
            break;
        case 4:
            _clearrole();
            break;
        case 5:
            break;
        default:
            {
                printf("输入错误！按回车确认返回主菜单！\n");
                _enter();
                _enter();
                showmenu();
            }
    }
}

void _desk()
{
    DWORD dwSize = MAX_PATH;
    char szLogicalDrives[MAX_PATH] = {0};
    DWORD dwResult = GetLogicalDriveStrings(dwSize,szLogicalDrives);
    if (dwResult > 0 && dwResult <= MAX_PATH)
    {
        char* szSingleDrive = szLogicalDrives;
        while(*szSingleDrive)
        {
            printf("Drive: %s\n", szSingleDrive);
            putDrivesType(szSingleDrive);
            putDrivesFreeSpace(szSingleDrive);
            GetDirverInfo(szSingleDrive);
            printf("\n");
            szSingleDrive += strlen(szSingleDrive) + 1;
        }
    }
    printf("已查询完所有磁盘，按回车键确认返回主菜单！\n");
    _enter();
    _enter();
    showmenu();
}

void _setrole()
{
    printf("请输入预设相对路径：");
    cin>>s1;
    _enter();
    s1=s1+"//";
    printf("设置完成，按回车键确认返回主菜单！\n");
    _enter();
    showmenu();
}

void _clearrole()
{
    s1="";
    printf("清除成功，按回车键确认返回主菜单！\n");
    _enter();
    _enter();
    showmenu();
}

void _enter()
{
    char ch;
    ch=getchar();
    printf("\n");
}

void putDrivesType(const char* lpRootPathName)
{
    UINT uDriverType = GetDriveType(lpRootPathName);
    switch(uDriverType)
    {
        case DRIVE_UNKNOWN  :
            puts("未知的磁盘类型");
            break;
        case DRIVE_NO_ROOT_DIR:
            puts("路径无效");
            break;
        case DRIVE_REMOVABLE:
            puts("可移动磁盘");
            break;
        case DRIVE_FIXED:
            puts("固定磁盘");
            break;
        case DRIVE_REMOTE:
            puts("网络磁盘");
            break;
        case DRIVE_CDROM:
            puts("光驱");
            break;
        case DRIVE_RAMDISK:
            puts("内存映射盘");
            break;
        default:
            break;
    }

}

void putDrivesFreeSpace(const char* lpRootPathName)
{
    unsigned long long available,total,free;
    if(GetDiskFreeSpaceEx(lpRootPathName,(ULARGE_INTEGER*)&available,(ULARGE_INTEGER*)&total,(ULARGE_INTEGER*)&free))
    {
        char a[6]="vol ";
        char b[5]="";
        strcat(a,strncpy(b,lpRootPathName,2));
        system(a);
        printf("total = %lld MB\nused = %lld MB\nfree = %lld MB\n",total>>20,(total>>20)-(available>>20),free>>20);
    }
    else
    {
        puts("获取容量信息失败");
    }
}

BOOL GetDirverInfo(LPSTR szDrive)
{
    TCHAR szFileSystemNameBuffer[BUFSIZE];

    if (!GetVolumeInformation(
        szDrive, NULL, 0,0,0,0,
        szFileSystemNameBuffer,
        BUFSIZE
        ))
    {
        return FALSE;
    }
    printf ("System Type is %s\n",szFileSystemNameBuffer);
    return TRUE;
}
