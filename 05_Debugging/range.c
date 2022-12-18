#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    int M = 0;
    int N = 0;
    int S = 1;

    if (argc == 1)
    {
        printf("Usage:\none arg - print range from 0 to arg\n");
        printf("two args - print range from arg1 to arg2\n");
        printf("three args - print range from arg1 to arg2 with step arg3\n");
        return 0;
    }
    else if (argc == 2)
    {
        N = atoi(argv[1]);
    }
    else if (argc == 3)
    {
        M = atoi(argv[1]);
        N = atoi(argv[2]);
    }
    else if (argc >= 4)
    {
        M = atoi(argv[1]);
        N = atoi(argv[2]);
        S = atoi(argv[3]);
    }
    else
    {
        printf("What the hack is argc???\n");
        return 1;
    }

    int i = 0;
    for (i = M; i < N; i += S)
        printf("%d\n", i);

    if (i - S != N - 1)
    {
        printf("%d\n", N-1);
    }
    return 0;
}