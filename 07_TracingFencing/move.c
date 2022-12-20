#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

void print_error_and_exit(int error_code, const char* file, const char* fun_name, int fd1, int fd2, const char* remove_file)
{
    char *errorbuf = strerror(error_code);
    printf("File %s %s error: %s\n", file, fun_name, errorbuf);
    if (fd1)
        close(fd1);
    if (fd2)
        close(fd2);
    if (remove_file)
        remove(remove_file);
    exit(error_code);
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Usage: ./move infile outfile\n");
        return 1;
    }
    errno = 0;
    int fd1 = open(argv[1], O_RDONLY);
    if (errno != 0)
    {
        print_error_and_exit(errno, argv[1], "open", 0, 0, NULL);
    }

    errno = 0;
    int fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (errno != 0)
    {
        print_error_and_exit(errno, argv[1], "open", fd1, fd2, argv[2]);
    }

    struct stat file_stat;
    errno = 0;
    fstat(fd1, &file_stat);
    if (errno != 0)
    {
        print_error_and_exit(errno, argv[1], "fstat", fd1, fd2, argv[2]);
    }
    int size = file_stat.st_size;
    char* file_str = malloc(size);

    errno = 0;
    read(fd1, file_str, size);
    if (errno != 0)
        print_error_and_exit(errno, argv[1], "read", fd1, fd2, argv[2]);

    errno = 0;
    write(fd2, file_str, size);
    if (errno != 0)
        print_error_and_exit(errno, argv[2], "write", fd1, fd2, argv[2]);

    errno = 0;
    close(fd1);
    if (errno != 0)
        print_error_and_exit(errno, argv[1], "close", fd1, fd2, argv[2]);

    errno = 0;
    close(fd2);
    if (errno != 0)
        print_error_and_exit(errno, argv[2], "close", 0, fd2, argv[2]);

    errno = 0;
    remove(argv[1]);
    if (errno != 0)
    {
        print_error_and_exit(errno, argv[1], "remove", 0, 0, NULL);
    }
    return 0;
}
