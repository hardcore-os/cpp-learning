#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
typedef int (*CAC_FUNC)(int, int);
int add(int a,int b)
{
    printf("call caculate1.c add\n");
    return (a + b);
}

int sub(int a, int b)
{
    CAC_FUNC cac_func = NULL;
    *(void **) (&cac_func) = dlsym(RTLD_NEXT, "sub");
   printf("call caculate1.c sub\n");
    return cac_func(  a,   b) ;
}

int mul(int a, int b)
{
    printf("call caculate1.c mul\n");
    return (a * b);
}


int div(int a, int b)
{
   CAC_FUNC cac_func = NULL;
    *(void **) (&cac_func) = dlsym(RTLD_NEXT, "div");
    printf("call caculate1.c div\n");
    return cac_func(  a,   b) ;
}

