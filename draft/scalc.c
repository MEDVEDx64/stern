#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void PrintString(const char *string)
{
    if (!string) {
        fprintf(stderr, "string is null");
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

char *Calc(char a, int b, int c)
{
    switch (a) {
        case '+': {
            char *r  = malloc(1024);
            sprintf(r, "%d", b+c);
            return r;       
        } break;
        case '-': {
            char *r  = malloc(1024);
            sprintf(r, "%d", b-c);
            return r;       
        } break;
        case '*': {
            char *r  = malloc(1024);
            sprintf(r, "%d", b*c);
            return r;       
        } break;
        case '/': {
            char *r  = malloc(1024);
            if (!c) {
                fprintf(stderr, "Division by zero!\n");
                exit(0);
            }
            sprintf(r, "%d", b/c);
            return r;       
        } break;
        case '?': {
            char *r  = malloc(1024);
            sprintf(r, "%d", rand()%(c-b)+b);
            return r;       
        } break;
        default: return 0;
    }
}

int ProcMath(char *s) //функция изменяет строку!
{
    if (!s) {
        fprintf(stderr, "string is null");
        return 0;
    }

    int i = 0; //итератор
    int a = 0; //действие(+-*/?)
    int b = 0; //1й операнд
    int c = 0; //2й операнд

    while (s[i] == ' ' || s[i] == '\t') {
        if (!s[i]) return 0;
        i++;
    } //пропускаем все пробелы
    if (s[i++] != '[') return 0; //проверяем первый символ
    while (s[i] == ' ' || s[i] == '\t') {
        if (!s[i]) return 0;
        i++;
    } //пропускаем все пробелы
    a = s[i++];
    if (a != '+' && a != '-' && a != '*' && a != '/' && a != '?') return 0; //проверяем знак
    while (s[i] == ' ' || s[i] == '\t') {
        if (!s[i]) return 0;
        i++;
    } //пропускаем все пробелы
    if (sscanf(s+i, "%d%d", &b, &c) != 2) return 0; //читаем числа
    while (s[i] != ']') {
        if (!s[i]) return 0;
        i++;
    } //находим конец операции
    if (i>=strlen(s)) return 0; //проверка на наличие конца операции
    
    char *buf = Calc(a,b,c); //выполняем операцию
    if (!buf) return 0;
    
//printf("buf: %s\ns: %s\n", buf, s);
    
    //изменяем строку 
    char tmp1[1024];
    sprintf(tmp1, "%s%s", buf, s + ++i);
    s = strcpy(s, tmp1);
/*    
    int j = 0;
    for (j = 0; j < strlen(buf); j++) s[j] = buf[j]; //копируем результат
    free(buf);

    for (; s[i-1]; i++, j++) {
        s[j] = s[i];
    }
*/          
    return 1;
}

int TestMath(char *s) //функция изменяет строку!
{
    if (!s) {
        fprintf(stderr, "string is null");
        return 0;
    }

    int i;
    for  (i = 0; i < strlen(s); i++) {
        if (s[i] == '[' && ProcMath(s+i)) return 1;
    }

    return 0;
}

main() 
{
    while (!feof(stdin)) { //пока файл не закончится
        char *s = GetString(); //находим строку
        if (!s) continue;
        
        while (TestMath(s)); //пока строка содержит мат. выражения преобразуем её
        
        PrintString(s); //выводим строку на экран
        
        free(s);
    }
    
    return 0;
}
