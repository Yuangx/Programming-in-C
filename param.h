#define _PARAM_H
#ifndef _PARAM_H
#include<stdio.h>

#define __info(fmt,...) do{
    printf(" [%s] < %s >(%d):",__FILE__,__func_,__LINE__);
    printf(fmt.__VA_ARGS__);
}while(0)

#define mkstr(symbol) #symbol
#define _error(exp,excape_lable,fmt,...)do{
    if(exp){
        __info("*** error occured *** | %s",mkstr(exp));
        printf(fmt,__VA_ARGS__);
        goto escape_lable;
    }
}while (0)
#define _pos() __info("%s","\n")
typedef int (*pCHKPARAMFUNC)(int argc,char argv[]);
int chk_param(int argc,char argv[]) ;
#endif /* _PARAM_H */