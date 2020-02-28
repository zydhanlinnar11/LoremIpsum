#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct d_Node {
    char string[101];
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

void dq_pushBack(deque * dq, char * string) {
    dequeNode * newNode = (dequeNode *) malloc(sizeof(dequeNode));
    if(newNode) {
        dq->size++;
        strcpy(newNode->string, string);
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

void dq_pushFront(deque * dq, char * string) {
    if(dq_isEmpty(dq))
        dq_pushBack(dq, string);
    else {
        dequeNode * newNode = (dequeNode *) malloc(sizeof(dequeNode));
        if(newNode) {
            dq->size++;
            strcpy(newNode->string, string);
            newNode->prev = NULL;
            newNode->next = dq->head;
            dq->head = newNode;
        }
    }
}

char * dq_front(deque * dq) {
    if(!dq_isEmpty(dq))
        return dq->head->string;
    else return "NULL";
}

char * dq_back(deque * dq) {
    if(!dq_isEmpty(dq))
        return dq->tail->string;
    else return "NULL";
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
    deque dq;
    initDeque(&dq);
    dq_pushBack(&dq, "Mantap");
    printf("front: %s, back: %s\n", dq_front(&dq), dq_back(&dq));
    dq_popBack(&dq);
    dq_pushBack(&dq, "Mantap");
    dq_pushBack(&dq, "Jiwa");
    dq_pushFront(&dq, "anjay");
    printf("front: %s, back: %s\n", dq_front(&dq), dq_back(&dq));
    dq_popFront(&dq);
    printf("front: %s, back: %s\n", dq_front(&dq), dq_back(&dq));
    dq_popFront(&dq);
    dq_popFront(&dq);
    printf("front: %s, back: %s\n", dq_front(&dq), dq_back(&dq));
    return 0;
}