#include <stdio.h>
int add(int a,int b)
{
    printf("call caculate.c add\n");
    return (a + b);
}

int sub(int a, int b)
{
    printf("call caculate.c sub\n");
    return (a - b);
}

int mul(int a, int b)
{
    printf("call caculate.c mul\n");
    return (a * b);
}

int div(int a, int b)
{
    printf("call caculate.c div\n");
    return (a / b);
}
