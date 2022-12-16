#include <ncurses.h>
#include <locale.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define DX 3

char** get_strings_from_file(char* filename, int* str_count) {
    int strings_count = 0;
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        printf("Can't open file %s\n", filename);
        return NULL;
    }
    
    struct stat file_stat;

    fstat(fd, &file_stat);
    int size = file_stat.st_size;
    char** strings = (char**) malloc(size * sizeof(char*));
    char* file_str = (char*)malloc(size);
    read(fd, file_str, size);

    char* string_start = file_str;
    for (int i = 0; i < size; i++)
    {
        printf("strings = %lx strings_start = %lx i = %d char = %c strings_count = %d size = %d malloc size = %lx\n", (long) strings, (long) string_start, i, *(file_str + i), strings_count, size, (long) (file_str + i - string_start));
        if (*(file_str + i) == '\n')
        {
            strings_count++;
            strings[strings_count-1] = malloc(file_str + i - string_start);
            memcpy(strings[strings_count-1], string_start + 1, file_str + i - string_start);
            string_start = file_str + i;
            printf("%s\n", strings[strings_count-1]);
        }
    }
    free(file_str);
    *str_count = strings_count;
    return strings;
}

int main(int argc, char** argv) {
    if (argc < 2)
    {
        printf("Please set file that would be shown!\n");
        return 1;
    }
    WINDOW *win;
    char c;
    int strings_count;
    char** strings = get_strings_from_file(argv[1], &strings_count);
    if (strings == NULL)
    {
        return 1;
    }
    int current_first_string = 0;

    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();

    addstr(argv[1]);
    refresh();

    win = newwin(LINES-2*DX, COLS-2*DX, DX, DX);
    keypad(win, TRUE);
    scrollok(win, TRUE);
    int lines_count = LINES-2*DX;

    //wmove(win, 1, 0);
    //wprintw(win, "LINES %d COLS %d\n", LINES, COLS);
    //wrefresh(win);
    //wmove(win, LINES-2*DX - 5, 1);
    for (int i = 0; i < lines_count; i++)
    {
        wprintw(win, " %3d  %s", i, strings[i]);
    }
    box(win, 0, 0);
    wrefresh(win);

    while ((c = wgetch(win)) != 27) {
        if (c == 2 || c == 32) // down
        {
            if (current_first_string + lines_count > strings_count)
            {
                continue;
            }
            current_first_string++;
        }
        else if (c == 3) // up
        {
            if (current_first_string <= 0)
            {
                continue;
            }
            current_first_string--;
        }
        werase(win);
        for (int i = current_first_string; i < current_first_string + lines_count && i < strings_count; i++)
        {
            wprintw(win, " %3d  %s", i, strings[i]);
        }
        box(win, 0, 0);
        wrefresh(win);
        /*
        wprintw(win, "  Key: %d, Name: %s\n", c, keyname(c));
        box(win, 0, 0);
        wrefresh(win);*/
    }
    endwin();
    return 0;
}
