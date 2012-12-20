#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static struct Define {
    char *name;
    char **strs;
    int num;
    struct Define *next;
} *head = 0;

void PrintString(const char *string)
{
    if (!string) {
        fprintf(stderr, "%s: NULL string recieved\n", __FUNCTION__);
        return;
    }
    
    while (string[0] == ' ' || string[0] == '\t') string++;
    
    fprintf(stdout, "%s", string);
}

char *GetString()
{
    char *buf = malloc(1024);
    if (fgets(buf, 1024, stdin)) return buf;
    
    free(buf);
    return 0;
}

int TestDefine(const char *s)
{
    if (!s) {
        fprintf(stderr, "%s: NULL string recieved\n", __FUNCTION__);
        return 0;
    }
    
    if ((s++)[0] != '@') return 0;
    char buf[1024];
    if (sscanf(s, "%s", buf) != 1) return 0;

    return 1;    
}

int TestCommand(const char *s)
{
    if (!s) {
        fprintf(stderr, "%s: NULL string recieved\n", __FUNCTION__);
        return 0;
    }
    
    if ((s++)[0] != '~') return 0;
    char buf[1024];
    if (sscanf(s, "%s", buf) != 1) return 0;

    return 1;    
}

void ProcCommand(const char *s)
{
    if (!s) {
        fprintf(stderr, "%s: NULL string recieved\n", __FUNCTION__);
        return;
    }
    
    if ((s++)[0] != '~') return;
    char buf[1024];
    if (sscanf(s, "%s", buf) != 1) return;

    struct Define *it = head;
    while (it) {
        if (!strcmp(it->name, buf)) {
            //выполняем команду
            int i;
            for (i = 0; i<it->num; i++) 
                PrintString(it->strs[i]);
            
            return;
        }

        it = it->next;
    }
    
    PrintString(s);
}

char **GetStrings(int *num)
{
    if (!num) {
        fprintf(stderr, "Unknown error in %s\n", __FUNCTION__);
        return 0;
    }
    
    char **res = malloc(sizeof(char*)*1024);
    
    for (*num = 0; *num < 1024; (*num)++) {
        res[*num] = GetString();
        char tmp[1024];
        sscanf(res[*num], "%s", tmp);
        if (tmp[0] == '@') {
            free(res[(*num)]);
            break;
        }
    }

    return res;
}

char *GetDefineName(const char *s)
{
    if (!s) {
        fprintf(stderr, "%s: NULL string recieved\n", __FUNCTION__);
        return 0;
    }
    
    if ((s++)[0] != '@') return 0;
    char *buf = malloc(1024);
    if (sscanf(s, "%s", buf) != 1) return 0;
    return buf;    
}

void AddDefine(const char *s)
{
    if (!s) return;

    struct Define *new_define = malloc(sizeof(struct Define));
    new_define->num = 0;
    new_define->strs = GetStrings(&(new_define->num)); //находим строчки учавствующие в define
    new_define->name = GetDefineName(s);
    new_define->next = head;
    head = new_define;
}

main() 
{
    while (!feof(stdin)) { //пока файл не закончится
        char *s = GetString(); //находим строку
        if (!s) continue;
        
        if (TestDefine(s)) { //проверяем, на то, что это дефайн
            AddDefine(s); //добавляем дефайн в стек 
        }
        else if (TestCommand(s)) {
            ProcCommand(s);
        }
        else PrintString(s);
        
        free(s);
    }
    
    return 0;
}
