#include<iostream>
#include<io.h>
#include<cstdio>
#include<time.h>
//���ļ�����
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

    printf("����������ѯ��Ŀ¼��");
    cin>>s;
    s=s1+s;
    _enter();
    long handle;//���ڲ��Ҿ��
    struct _finddata_t fileinfo;//�ļ���Ϣ�Ľṹ��
    while(s.empty() || _access(s.c_str(), 0) != 0)
    {
        printf("��·�������س���ȷ�Ϸ������˵���\n");
        _enter();
        showmenu();
        return;
    }

    const char* to_search= s.data();
    result = _stat( to_search, &buf );
    handle=_findfirst(to_search,&fileinfo);//��һ�β���
    if(-1==handle)
    {
        printf("��ѯ�������ļ������س���ȷ�Ϸ������˵���\n");
        _enter();
        showmenu();
        return;
    }
    if(_S_IFREG & buf.st_mode)
    {
        printf("����Ϊ�ļ����ļ���Ϊ�� ");
        printf("%s\n",fileinfo.name);//��ӡ����һ���ļ���
        printf("�ļ���СΪ�� ");
        printf("%d �ֽ�\n",fileinfo.size);
        printf("��������Ϊ�� ");
        printf("%s\n",asctime(localtime(&fileinfo.time_create)));
        printf("���һ�α༭����Ϊ�� ");
        printf("%s\n",asctime(localtime(&fileinfo.time_write)));
        printf("���һ�η�������Ϊ�� ");
        printf("%s\n",asctime(localtime(&fileinfo.time_access)));
        _findclose(handle);//�����˹رվ��
        printf("�Ѳ�ѯ�������ļ������س���ȷ�Ϸ������˵���\n");
        _enter();
        showmenu();
    }
    else if(_S_IFDIR & buf.st_mode)
    {
        printf("����Ϊ�ļ��У��ļ�����Ϊ�� ");
        printf("%s\n",fileinfo.name);//��ӡ����һ���ļ���
        printf("��������Ϊ�� ");
        printf("%s\n",asctime(localtime(&fileinfo.time_create)));
        printf("���һ�α༭����Ϊ�� ");
        printf("%s\n",asctime(localtime(&fileinfo.time_write)));
        printf("���һ�η�������Ϊ�� ");
        printf("%s\n",asctime(localtime(&fileinfo.time_access)));
        printf("���ļ��а����������ݣ�\n");
        int nRet= (handle <0 ) ? -1 : 1;

        string st = s + "\\*.*";

        const char* to_search2= st.data();
        long handle2;
        int x=0,y=0;

        handle2 = _findfirst(to_search2,&fileinfo);
        while ( nRet >= 0 )
        {
            if ( fileinfo.attrib == _A_SUBDIR )   // �����Ŀ¼
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
        printf("·���¹��� %d ����Ŀ������%d ���ļ��У�%d ���ļ���\n",x+y,x,y);

        _findclose(handle);//�����˹رվ��
        printf("�Ѳ�ѯ�������ļ������س���ȷ�Ϸ������˵���\n");
        _enter();
        showmenu();
    }
}

void showmenu()
{
    printf("----------------��ӭʹ�ñ��η���----------------\n");
    printf("\t1  ��ѯ�ļ�/�ļ�����Ϣ\n");
    printf("\t2  ��ѯ������Ϣ\n");
    printf("\t3  �������·��\n");
    printf("\t4  ������·��\n");
    printf("\t5  �˳�����\n");
    printf("���������ѡ��˵���");
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
                printf("������󣡰��س�ȷ�Ϸ������˵���\n");
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
    printf("�Ѳ�ѯ�����д��̣����س���ȷ�Ϸ������˵���\n");
    _enter();
    _enter();
    showmenu();
}

void _setrole()
{
    printf("������Ԥ�����·����");
    cin>>s1;
    _enter();
    s1=s1+"//";
    printf("������ɣ����س���ȷ�Ϸ������˵���\n");
    _enter();
    showmenu();
}

void _clearrole()
{
    s1="";
    printf("����ɹ������س���ȷ�Ϸ������˵���\n");
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
            puts("δ֪�Ĵ�������");
            break;
        case DRIVE_NO_ROOT_DIR:
            puts("·����Ч");
            break;
        case DRIVE_REMOVABLE:
            puts("���ƶ�����");
            break;
        case DRIVE_FIXED:
            puts("�̶�����");
            break;
        case DRIVE_REMOTE:
            puts("�������");
            break;
        case DRIVE_CDROM:
            puts("����");
            break;
        case DRIVE_RAMDISK:
            puts("�ڴ�ӳ����");
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
        puts("��ȡ������Ϣʧ��");
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
