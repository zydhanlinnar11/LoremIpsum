#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct _StackNode {
    char huruf;
    struct _StackNode * next;
} StackNode;

typedef struct _stack {
    StackNode * top;
    unsigned size;
} stack;

bool st_isEmpty(stack * st) { return (st->top == NULL && st->size == 0); }

void initStack(stack * st) {
    st->top = NULL;
    st->size = 0;
}

unsigned st_getSize(stack * st) { return st->size; }

void st_push(stack * st, char huruf) {
    StackNode * newStackNode = (StackNode *) malloc(sizeof(StackNode));
    if(newStackNode) {
        st->size++;
        newStackNode->huruf = huruf;

        if(st_isEmpty(st))
            newStackNode->next = NULL;
        else
            newStackNode->next = st->top;
        
        st->top = newStackNode;
    } else puts("Memorynya ga cukup slur");
}

void st_pop(stack * st) {
    if(!st_isEmpty(st)) {
        StackNode * tmp = st->top;
        if(st->size-- == 1)
            st->top = NULL;
        else
            st->top = tmp->next;
        free(tmp);
    }
}

char st_top(stack * st) {
    if(!st_isEmpty(st))
        return st->top->huruf;
    else return -1;
}

bool isPalindrom(char * string, stack * st) {
    unsigned i;
    for(i=0; i<strlen(string); i++) {
        if(string[i] != st_top(st))
            return false;
        st_pop(st);
    }
    return true;
}

int main() {
    char a[100];
    unsigned i;
    stack st;
    initStack(&st);
    gets(a);
    for(i=0; i<strlen(a); i++)
        st_push(&st, a[i]);
    if(isPalindrom(a, &st))
        puts("palindrom");
    else if(strcmp(a, "macbook pro") == 0)
        puts("mahal, eh bukan palindrom deh");
    else puts("bukan palindrom");
    return 0;
}