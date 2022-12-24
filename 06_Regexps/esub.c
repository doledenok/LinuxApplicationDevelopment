#include <regex.h>
#include <stdio.h>
#include <string.h>

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
    char* string = argv[3];
    char* subst = argv[2];
    char new_string[strlen(string) + strlen(subst)];

    ret = regcomp(&regex, argv[1], REG_EXTENDED);
    if (ret)
    {
        regerror(ret, &regex, error_buffer, sizeof(error_buffer));
        printf("Regex compilation failed: %s\n", error_buffer);
        return 1;
    }

    ret = regexec(&regex, string, MATCH_COUNT, pmatch, 0);
    if (!ret)
    {
        int new_string_len = pmatch[0].rm_so;
        strncpy(new_string, string, pmatch[0].rm_so);

        int match_count = 0;
        for (int i = 1; pmatch[i].rm_so != -1; i++)
        {
            match_count++;
        }
        for (int i = 0; i < strlen(subst); i++)
        {
            if (subst[i] == '\\' && i < strlen(subst) - 1 && subst[i + 1] < '9' && subst[i + 1] > '0')
            {
                int match_num = subst[i + 1] - '0';
                //printf("if %s %d %d %s %d\n", string + pmatch[match_num].rm_so, pmatch[match_num].rm_so, pmatch[match_num].rm_eo, new_string, new_string_len);
                if (match_num > match_count)
                {
                    printf("Wrong match number: %d\n", match_num);
                    return 1;
                }
                strncpy(new_string + new_string_len, string + pmatch[match_num].rm_so, pmatch[match_num].rm_eo - pmatch[match_num].rm_so);
                new_string_len += pmatch[match_num].rm_eo - pmatch[match_num].rm_so;
                i++;
            }
            else
            {
                //printf("else %c %s %d\n", subst[i], new_string, new_string_len);
                new_string[new_string_len] = subst[i];
                new_string_len++;
            }
            
        }
        new_string[new_string_len] = '\0';
        printf("%s%s\n", new_string, (char *) (string + pmatch[0].rm_eo));   
    }
    else if (ret == REG_NOMATCH)
    {
        printf("%s\n", string);
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
