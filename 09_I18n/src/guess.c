#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <libintl.h>
#include <config.h>

#define _(STRING) gettext(STRING)

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    bindtextdomain("guess", LOCALE_PATH);
    textdomain("guess");

    int middle, l = 1, r = 100;
    char answer[100];

    printf(_("Please think a number between %d and %d\n"), l, r);
    while (l < r)
    {
        middle = (l + r) / 2;
        while(1)
        {
            printf(_("Is your number larger than %d?\n"), middle);
            if (scanf("%s", answer) <= 0)
                continue;
            if (!strcmp(answer, _("yes")))
            {
                l = middle + 1;
                break;
            }
            else if (!strcmp(answer, _("no")))
            {
                r = middle;
                break;
            }
        }
    }
    printf(_("Your number is %d\n"), r);
    return 0;
}
