#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

//动态链接库路径
#define LIB_CACULATE_PATH "./libcaculate.so"

//函数指针
typedef int (*CAC_FUNC)(int, int);

int main()
{
    void *handle;
    char *error;
    CAC_FUNC cac_func = NULL;

    //获取一个函数
    *(void **) (&cac_func) = dlsym(RTLD_NEXT, "add");
    if ((error = dlerror()) != NULL)  {
    fprintf(stderr, "%s\n", error);
    exit(EXIT_FAILURE);
    }
    printf("main[add]: %d\n", (*cac_func)(2,7));

    cac_func = (CAC_FUNC)dlsym(RTLD_NEXT, "sub");
    printf("main[sub]: %d\n", cac_func(9,2));

    cac_func = (CAC_FUNC)dlsym(RTLD_NEXT, "mul");
    printf("main[mul]: %d\n", cac_func(3,2));

    cac_func = (CAC_FUNC)dlsym(RTLD_NEXT, "div");
    printf("main[div]: %d\n", cac_func(8,2));

    exit(EXIT_SUCCESS);
}
