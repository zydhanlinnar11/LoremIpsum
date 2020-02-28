#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct _StackNode {
    char string[101];
    struct _StackNode * next;
} StackNode;

typedef struct _stack {
    StackNode * top;
    unsigned size;
} stack;

bool st_isEmpty(stack * st) { return (st->top == NULL); }

void initStack(stack * st) {
    st->top = NULL;
    st->size = 0;
}

unsigned st_getSize(stack * st) { return st->size; }

void st_push(stack * st, char * string) {
    StackNode * newStackNode = (StackNode *) malloc(sizeof(StackNode));
    if(newStackNode) {
        st->size++;
        strcpy(newStackNode->string, string);

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

char * st_top(stack * st) {
    if(!st_isEmpty(st))
        return st->top->string;
    else return "NULL";
}

int main() {
    stack st;
    initStack(&st);
    puts(st_top(&st));
    st_pop(&st);
    printf("size : %d\n", st_getSize(&st));
    st_push(&st, "Njay");
    puts(st_top(&st));
    printf("size : %d\n", st_getSize(&st));
    st_pop(&st);
    puts(st_top(&st));
    st_push(&st, "Sakit");
    st_push(&st, "slur");
    puts(st_top(&st));
    st_pop(&st);
    puts(st_top(&st));
    printf("size : %d\n", st_getSize(&st));
    return 0;
}