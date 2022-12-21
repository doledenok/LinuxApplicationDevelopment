#include "rhash.h"
#include <string.h>
#include <errno.h>
#include "config.h"

#ifdef CHANGE_INPUT
#include <readline/readline.h>
#endif

void print_hash_of_file(int type, int output_type, const char* filepath)
{
    char digest[64];
    char output[130];
    int res = rhash_file(type, filepath, digest);
    if(res < 0)
    {
        fprintf(stderr, "LibRHash error: %s: %s\n", filepath, strerror(errno));
        return;
    }
    rhash_print_bytes(output, digest, rhash_get_digest_size(type),
       (output_type | RHPR_UPPERCASE));
    printf("%s\n", output);
}

void print_hash_of_string(int type, int output_type, const char* string)
{
    char digest[64];
    char output[130];
    int res = rhash_msg(type, string, strlen(string), digest);
    if(res < 0)
    {
        fprintf(stderr, "message digest calculation error\n");
        return;
    }
    rhash_print_bytes(output, digest, rhash_get_digest_size(type),
       (output_type | RHPR_UPPERCASE));
    printf("%s\n", output);
}

void print_hash(const char* type, const char* string)
{
    int output_type = RHPR_HEX;
    if (!strcmp(type, "md5"))
    {
        int type = RHASH_MD5;
        output_type = RHPR_BASE64;
        if (string[0] == '"')
            print_hash_of_string(type, output_type, string);
        else
            print_hash_of_file(type, output_type, string);
    }
    else if (!strcmp(type, "MD5"))
    {
        int type = RHASH_MD5;
        if (string[0] == '"')
            print_hash_of_string(type, output_type, string);
        else
            print_hash_of_file(type, output_type, string);
    }
    else if (!strcmp(type, "sha1"))
    {
        int type = RHASH_SHA1;
        output_type = RHPR_BASE64;
        if (string[0] == '"')
            print_hash_of_string(type, output_type, string);
        else
            print_hash_of_file(type, output_type, string);
    }
    else if (!strcmp(type, "SHA1"))
    {
        int type = RHASH_SHA1;
        if (string[0] == '"')
            print_hash_of_string(type, output_type, string);
        else
            print_hash_of_file(type, output_type, string);
    }
    else if (!strcmp(type, "tth"))
    {
        int type = RHASH_TTH;
        output_type = RHPR_BASE64;
        if (string[0] == '"')
            print_hash_of_string(type, output_type, string);
        else
            print_hash_of_file(type, output_type, string);
    }
    else if (!strcmp(type, "TTH"))
    {
        int type = RHASH_TTH;
        if (string[0] == '"')
            print_hash_of_string(type, output_type, string);
        else
            print_hash_of_file(type, output_type, string);
    }
    else
    {
        printf("Unknown type of hashing: %s\n", type);
    }    
}

int main(int argc, char **argv)
{
    int i, nread = 0;
    size_t len;
    char* line;
    char* token1;
    char* token2;

    rhash_library_init();

    while(1)
    {
        printf("> ");
        #ifdef CHANGE_INPUT
        line = readline(NULL);
        nread = (line) ? 0 : -1;

        #else
        nread = getline(&line, &len, stdin);
        #endif

        if (nread == -1)
        {
            break;
        }
        
        token1 = strtok(line, " ");
        if (!token1)
        {
            printf("No second argument: string or file\n");
            continue;
        }
        else if (!(token2 = strtok(NULL, " ")))
        {
            printf("No second argument: string or file\n");
            continue;
        }
        if (token2[strlen(token2) - 1] == '\n')
        {
            token2[strlen(token2) - 1] = '\0';
        }
        print_hash(token1, token2);
    }
    return 0;
}
