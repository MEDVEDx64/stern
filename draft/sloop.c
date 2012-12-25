#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void PrintString(const char *string)
{
    if (!string) {
        fprintf(stderr, "string is null");
        return;
    }
    
    while (string[0] == ' ' || string[0] == '\t') string++;
    
    fprintf(stdout, "%s", string);
}

void LoopString(const char *s, int i)
{
    if (!s) {
        fprintf(stderr, "string is null");     
        return;
    }
    
    int j = 0;
    for (j = 0; j<strlen(s); j++) {
        if (s[j] == '#') {
            fprintf(stdout, "%d", i);
        }
        else {
            fprintf(stdout, "%c", s[j]);
        }
    }
}

void LoopStrings(char **strs, int num, int i, int limit, int step)
{
    if (!strs) {
        fprintf(stderr, "strings is null");
        return;
    }
    
    int j;
    
    for (; i<limit; i += step) {
        for (j = 0; j<num; j++) {
            LoopString(strs[j], i);
        }
    }
}

char *GetString()
{
    char *buf = malloc(1024);
    if (fgets(buf, 1024, stdin)) return buf;
    
    free(buf);
    return 0;
}

int TestWhile(const char *s)
{
    if (!s) {
        fprintf(stderr, "string is null");
        return 0;
    }
    
    if ((s++)[0] != '!') return 0;

    char s1[3][1024];
    int _;
    if (sscanf(s, "%s%d%s%d%s%d",s1[0], &_, s1[1], &_, s1[2], &_) != 6) return 0;
    if (strcmp(s1[0], "from")) return 0;
    if (strcmp(s1[1], "to")) return 0;
    if (strcmp(s1[2], "by")) return 0;

    return 1;
}

char **GetStrings(int *num)
{
    if (!num) {
        fprintf(stderr, "unknown error");
        return 0;
    }
    
    char **res = malloc(sizeof(char*)*1024);
    
    for (*num = 0; *num < 1024; (*num)++) {
        res[*num] = GetString();
        char tmp[1024];
        sscanf(res[*num], "%s", tmp);
        if (tmp[0] == '!') {
            free(res[(*num)]);
            break;
        }
    }

    return res;
}

int GetStart(const char *s)
{
    if (!s) {
        fprintf(stderr, "string is null");
        return 0;
    }
    
    if ((s++)[0] != '!') {
        fprintf(stderr, "unknown start num");
        return 0;
    }
    
    char s1[3][1024];
    int _;
    int result;
    if (sscanf(s, "%s%d%s%d%s%d",s1[0], &result, s1[1], &_, s1[2], &_) != 6) return 0;
    if (strcmp(s1[0], "from")) return 0;
    if (strcmp(s1[1], "to")) return 0;
    if (strcmp(s1[2], "by")) return 0;

    return result;
}

int GetLimit(const char *s)
{
    if (!s) {
        fprintf(stderr, "string is null");
        return 0;
    }
    
    if ((s++)[0] != '!') {
        fprintf(stderr, "unknown start num");
        return 0;
    }

    char s1[3][1024];
    int _;
    int result;
    if (sscanf(s, "%s%d%s%d%s%d",s1[0], &_, s1[1], &result, s1[2], &_) != 6) return 0;
    if (strcmp(s1[0], "from")) return 0;
    if (strcmp(s1[1], "to")) return 0;
    if (strcmp(s1[2], "by")) return 0;

    return result;
}

int GetStep(const char *s)
{
    if (!s) {
        fprintf(stderr, "string is null");
        return 0;
    }
    
    if ((s++)[0] != '!') {
        fprintf(stderr, "unknown start num");
        return 0;
    }

    char s1[3][1024];
    int _;
    int result;
    if (sscanf(s, "%s%d%s%d%s%d",s1[0], &_, s1[1], &_, s1[2], &result) != 6) return 0;
    if (strcmp(s1[0], "from")) return 0;
    if (strcmp(s1[1], "to")) return 0;
    if (strcmp(s1[2], "by")) return 0;

    return result;
}

main() 
{
    while (!feof(stdin)) { //пока файл не закончится
        char *s = GetString(); //находим строку
        if (!s) continue;
        
        if (TestWhile(s)) { //проверяем, на то, что это цикл
            int num = 0;
            char **strs = GetStrings(&num); //находим строчки учавствующие в цикле
            if (strs) {
                LoopStrings(strs, num, GetStart(s), GetLimit(s), GetStep(s));
                while (num--) free(strs[num]);
                free(strs);
            }
        }
        else PrintString(s);
        
        free(s);
    }
    
    return 0;
}
