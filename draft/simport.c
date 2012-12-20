#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void PrintString(const char *string)
{
    if (!string) {
        fprintf(stderr, "%s: NULL string recieved\n", __FUNCTION__);
        return;
    }

    while (string[0] == ' ' || string[0] == '\t') string++;

    fprintf(stdout, "%s", string);
}

char *GetString(FILE *f)
{
    if (!f) return 0;

    char *buf = malloc(1024);
    if (fgets(buf, 1024, f)) return buf;

    free(buf);
    return 0;
}

int TestInclude(const char *s)
{
    if (!s) {
        fprintf(stderr, "%s: NULL string recieved\n", __FUNCTION__);
        return 0;
    }

    if ((s++)[0] != '<') return 0;
    char buf[1024];
    int i;
    for (i = 0; i < 1024; i++)
        if (s[i] != '>') {
            if (s[i] == '\0' || s[i] == '\n') return 0;
            else buf[i] = s[i];
        }
        else {
            buf[i]= 0;
            return 1;
        }

    return 0;
}

char *GetFileFromString(const char *s) 
{
    if (!s) {
        fprintf(stderr, "%s: NULL string recieved\n", __FUNCTION__);
        return 0;
    }

    if ((s++)[0] != '<') return 0;
    char *buf = malloc(1024);
    int i;
    for (i = 0; i < 1024; i++) 
        if (s[i] != '>') {
            if (s[i] == '\0' || s[i] == '\n') {
                free(buf);
                return 0;
            }
            else buf[i] = s[i];
        }
        else {
            buf[i]= 0;
            return buf;
        }

    free(buf);
    return 0;
}

void Proc(FILE *f)
{
    if (!f) {
        fprintf(stderr, "Can`t reach file.\n");
        return;
    }

    while (!feof(f)) { //пока файл не закончится
        char *s = GetString(f); //находим строку
        if (!s) continue;

        if (TestInclude(s)) { //проверяем, на то, что это инклюд
            char *tmp = GetFileFromString(s);
            if (tmp) {
                FILE *f = fopen(tmp, "r");
                Proc(f);
                free(tmp);
            }
            else {
                fprintf(stderr, "Hey, that file`s a spy!\n");
            }
        }
        else {
            PrintString(s);
        }

        free(s);
    }
}

main() 
{
    FILE *f = stdin;
    Proc(f);

    return 0;
}
