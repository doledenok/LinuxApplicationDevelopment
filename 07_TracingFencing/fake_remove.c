#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>
#include <unistd.h>

typedef int (*real_remove_t)(char *);

int real_remove(char *file)
{
    return ((real_remove_t) dlsym(RTLD_NEXT, "remove"))(file);
}

int remove(char *file)
{
    if (strstr(file, "PROTECT") != NULL)
    {
        return -1;
    }
    return real_remove(file);
}
