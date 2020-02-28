#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct _pQueueNode {
    int val;
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

void pq_push(pqueue * pq, int val) {
    pQueueNode * newNode = (pQueueNode *) malloc(sizeof(pQueueNode));
    if(newNode) {
        newNode->next = NULL;
        newNode->val = val;
        pq->size++;
        if(pq_isEmpty(pq)) {
            pq->top = newNode;
            return;
        }
        pQueueNode * tmp = pq->top, *prev = NULL;
        while(tmp != NULL && tmp->val < val) {
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

int pq_top(pqueue * pq) {
    if(pq_isEmpty(pq))
        return INT_MIN;
    else return pq->top->val;
}

void print(pqueue * pq) {
    pQueueNode * curr = pq->top;
    while(curr != NULL){
        printf("%d ", curr->val);
        curr = curr->next;
    }
}

int main() {
    pqueue pq;
    initPQueue(&pq);
    pq_push(&pq, 5);
    pq_push(&pq, 7);
    pq_push(&pq, 2);
    pq_push(&pq, 1);
    pq_push(&pq, 9);
    pq_push(&pq, 8);
    pq_pop(&pq);
    print(&pq);
    return 0;
}