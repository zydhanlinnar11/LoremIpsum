#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _StackNode {
    int val;
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

void st_push(stack * st, int val) {
    StackNode * newStackNode = (StackNode *) malloc(sizeof(StackNode));
    if(newStackNode) {
        st->size++;
        newStackNode->val = val;

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

int st_top(stack * st) {
    if(!st_isEmpty(st))
        return st->top->val;
    else return -1;
}

int main() {
    stack st;
    initStack(&st);
    unsigned t, command;
    int halah, q;
    scanf("%u", &t);
    while(t--) {
        scanf("%u", &command);
        if(command == 1) {
            scanf("%d", &q);
            st_push(&st, q);
        } else if(command == 2)
            st_pop(&st);
        else {
            halah = st_top(&st);
            if(halah == -1)
                printf("Empty!\n");
            else
                printf("%d\n", halah);
        }
    }
    return 0;
}