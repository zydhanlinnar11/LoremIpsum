#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct _pQueueNode {
    char string[101];
    struct _pQueueNode * next;
} pQueueNode;

typedef struct _pQueue {
    pQueueNode * top;
    unsigned size;
} pqueue;

void initPQueue(pqueue * pq) {
    pq->size = 0;
    pq->top = NULL;
}

bool pq_isEmpty(pqueue * pq) {
    return (pq->top == NULL);
}

void pq_push(pqueue * pq, char * string) {
    pQueueNode * newNode = (pQueueNode *) malloc(sizeof(pQueueNode));
    if(newNode) {
        newNode->next = NULL;
        strcpy(newNode->string, string);
        pq->size++;
        if(pq_isEmpty(pq)) {
            pq->top = newNode;
            return;
        }
        pQueueNode * tmp = pq->top, *prev = NULL;
        while(tmp != NULL && strcmp(tmp->string, string) < 0) {
            prev = tmp;
            tmp = tmp->next;
        }
        if(prev == NULL) {
            newNode->next = pq->top;
            pq->top = newNode;
        } else {
            newNode->next = tmp;
            prev->next = newNode;
        }
    }
}

void pq_pop(pqueue * pq) {
    if(!pq_isEmpty(pq)) {
        pQueueNode * tmp = pq->top;
        if(--pq->size == 0)
            pq->top = NULL;
        else
            pq->top = tmp->next;
        free(tmp);
    }
}

char * pq_top(pqueue * pq) {
    if(pq_isEmpty(pq))
        return "\0";
    else return pq->top->string;
}

void print(pqueue * pq) {
    pQueueNode * curr = pq->top;
    while(curr != NULL){
        printf("%s ", curr->string);
        curr = curr->next;
    }
}

int main() {
    pqueue pq;
    initPQueue(&pq);
    pq_push(&pq, "Abdan");
    pq_push(&pq, "Aadan");
    pq_push(&pq, "Fauzan");
    pq_push(&pq, "Yusril");
    puts(pq_top(&pq));
    // pq_pop(&pq);
    print(&pq);
    return 0;
}