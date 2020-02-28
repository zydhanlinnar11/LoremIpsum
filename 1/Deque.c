#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct d_Node {
    int val;
    struct d_Node * next, * prev;
} dequeNode;

typedef struct deq {
    unsigned size;
    dequeNode * head, * tail;
} deque;

void initDeque(deque * dq) {
    dq->size = 0;
    dq->head = dq->tail = NULL;
}

bool dq_isEmpty(deque * dq) {
    return (dq->head == NULL && dq->tail == NULL);
}

void dq_pushBack(deque * dq, int val) {
    dequeNode * newNode = (dequeNode *) malloc(sizeof(dequeNode));
    if(newNode) {
        dq->size++;
        newNode->val = val;
        newNode->next = NULL;
        if(dq_isEmpty(dq)) {
            newNode->prev = NULL;
            dq->head = dq->tail = newNode;
        } else {
            newNode->prev = dq->tail;
            dq->tail = newNode;
        }
    } else puts("Memory ga cukup slur");
}

void dq_pushFront(deque * dq, int val) {
    if(dq_isEmpty(dq))
        dq_pushBack(dq, val);
    else {
        dequeNode * newNode = (dequeNode *) malloc(sizeof(dequeNode));
        if(newNode) {
            dq->size++;
            newNode->val = val;
            newNode->prev = NULL;
            newNode->next = dq->head;
            dq->head = newNode;
        }
    }
}

int dq_front(deque * dq) {
    if(!dq_isEmpty(dq))
        return dq->head->val;
    else return INT_MIN;
}

int dq_back(deque * dq) {
    if(!dq_isEmpty(dq))
        return dq->tail->val;
    else return INT_MAX;
}

void dq_popBack(deque * dq) {
    if(!dq_isEmpty(dq)) {
        dequeNode * tmp = dq->tail;
        if(--dq->size == 0) 
            dq->head = dq->tail = NULL;
        else dq->tail = dq->tail->prev;
        free(tmp);
    }
}

void dq_popFront(deque * dq) {
    if(!dq_isEmpty(dq)) {
        dequeNode * tmp = dq->head;
        if(--dq->size == 0)
            dq->head = dq->tail = NULL;
        else dq->head = dq->head->next;
        free(tmp);
    }
}

int main() {
    return 0;
}