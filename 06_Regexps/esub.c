#include <regex.h>
#include <stdio.h>
//#include <stdlib.h>

#define MATCH_COUNT 100

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        printf("Usage: ./esub regexp substitution string\n");
        return 1;
    }

    regex_t regex;
    int ret;
    char error_buffer[100];
    regmatch_t pmatch[MATCH_COUNT];

    ret = regcomp(&regex, argv[1], REG_EXTENDED);
    if (ret)
    {
        regerror(ret, &regex, error_buffer, sizeof(error_buffer));
        printf("Regex compilation failed: %s\n", error_buffer);
        return 1;
    }

    ret = regexec(&regex, argv[3], MATCH_COUNT, pmatch, 0);
    if (!ret)
    {
        /*
        printf("%d %d\n", pmatch[0].rm_so, pmatch[0].rm_eo);
        printf("%d %d\n", pmatch[1].rm_so, pmatch[1].rm_eo);
        printf("%d %d\n", pmatch[2].rm_so, pmatch[2].rm_eo);
        printf("%d %d\n", pmatch[3].rm_so, pmatch[3].rm_eo);
        */
        fwrite(argv[3], 1, pmatch[0].rm_so, stdout);
        printf("%s%s\n", argv[2], (char *) (argv[3] + pmatch[0].rm_eo));   
    }
    else if (ret == REG_NOMATCH)
    {
        printf("%s\n", argv[3]);
    }
    else
    {
        regerror(ret, &regex, error_buffer, sizeof(error_buffer));
        printf("Regex match failed: %s\n", error_buffer);
        regfree(&regex);
        return 1;
    }

    regfree(&regex);
    return 0;
}
