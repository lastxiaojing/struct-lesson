#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxn 31

typedef struct _stack {
    char Q[maxn];
    int top;
}Stack;

void initialStack(Stack *S) {
    S->top = 0;
    S->Q[S->top] = 0;
}

void push(Stack *S, char val) {
    if(S->top >= maxn) {
        return ;
    }

    S->Q[S->top] = val;
    S->top += 1;
}

char top(Stack *S) {
    if(S->top < 0) {
        // stand for error
        return '$';
    }
    return S->Q[S->top - 1];
}

void pop(Stack *S) {
    if(S->top > 0) {
        S->top --;
    }
}

int size(Stack * sta) {
    return sta->top;
}

char * stringReverse(char * s) {
    int i = 0, j = 0;
    char str[maxn];
    while(s[i] != 0) {
        str[i] = s[i];
        i ++;
    }
    while(i > 0) {
        s[j] = str[j];
        i --;
        j ++;
    }
    s[j] = 0;
    return s;
}

char * octal(int number, char * res) {
    Stack sta;
    initialStack(&sta);

    int remai;
    char cremai;

    char arr[maxn];
    while(number > 0) {
        remai = number % 8;
        cremai = (char)('0' + remai);
        number /= 8;
        push(&sta, cremai);
    }

    int i = 0;
    while(size(&sta) > 0) {
        res[i ++] = top(&sta);
        pop(&sta);
    }
    res[i] = 0;

    stringReverse(res);

    return res;
}

int main(int argc, const char *argv[])
{
    int number;
    char res[maxn];
    while(scanf("%d", &number) != EOF) {
        memset(res, 0, sizeof(res));
        printf("%s\n", octal(number, res));
    }
    return 0;
}
