#include<iostream>
#include<windows.h>
#include<cstdio>
#include<string.h>

void putDrivesType(const char* lpRootPathName)
{
    UINT uDriverType = GetDriveType(lpRootPathName);
    switch(uDriverType) {
    case DRIVE_UNKNOWN  :puts("未知的磁盘类型"); break;
    case DRIVE_NO_ROOT_DIR: puts("路径无效"); break;
    case DRIVE_REMOVABLE: puts("可移动磁盘"); break;
    case DRIVE_FIXED: puts("固定磁盘"); break;
    case DRIVE_REMOTE: puts("网络磁盘"); break;
    case DRIVE_CDROM: puts("光驱"); break;
    case DRIVE_RAMDISK: puts("内存映射盘"); break;
    default: break;
    }

}

void putDrivesFreeSpace(const char* lpRootPathName)
{
    unsigned long long available,total,free;
    if(GetDiskFreeSpaceEx(lpRootPathName,(ULARGE_INTEGER*)&available,(ULARGE_INTEGER*)&total,(ULARGE_INTEGER*)&free)){
        char a[6]="vol ";
        char b[5]="";
        strcat(a,strncpy(b,lpRootPathName,2));
        system(a);
        printf("total = %lld MB\nused = %lld MB\nfree = %lld MB\n",total>>20,(total>>20)-(available>>20),free>>20);
    }else{
        puts("获取容量信息失败");
    }
}

int main()
{
    DWORD dwSize = MAX_PATH;
    char szLogicalDrives[MAX_PATH] = {0};
    DWORD dwResult = GetLogicalDriveStrings(dwSize,szLogicalDrives);
    if (dwResult > 0 && dwResult <= MAX_PATH) {
        char* szSingleDrive = szLogicalDrives;
        while(*szSingleDrive) {
            printf("Drive: %s\n", szSingleDrive);
            putDrivesType(szSingleDrive);
            putDrivesFreeSpace(szSingleDrive);
            printf("\n");
            szSingleDrive += strlen(szSingleDrive) + 1;
        }
    }
    return 0;
}
