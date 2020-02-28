#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

typedef struct _pas {
    unsigned id, urg;
} pasien;

typedef struct _pQueueNode {
    pasien orang;
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

void pq_push(pqueue * pq, pasien orang) {
    pQueueNode * newNode = (pQueueNode *) malloc(sizeof(pQueueNode));
    if(newNode) {
        newNode->next = NULL;
        newNode->orang = orang;
        pq->size++;
        if(pq_isEmpty(pq)) {
            pq->top = newNode;
            return;
        }
        pQueueNode * tmp = pq->top, *prev = NULL;
        while(tmp != NULL && tmp->orang.urg >= orang.urg) {
            if(tmp->orang.urg == orang.urg && orang.id <= tmp->orang.id)
                break;
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

pasien pq_top(pqueue * pq) {
    return pq->top->orang;
}

// void print(pqueue * pq) {
//     pQueueNode * curr = pq->top;
//     while(curr != NULL){
//         printf("%d ", curr->val);
//         curr = curr->next;
//     }
// }

int main() {
    pqueue pq;
    initPQueue(&pq);
    char command[8];
    unsigned i, id, urg;
    pasien tmp;
    scanf("%u", &i);
    while(i--) {
        scanf("%s", command);
        if(strcmp(command, "MASUK") == 0) {
            scanf("%u %u", &id, &urg);
            tmp.id = id, tmp.urg = urg;
            pq_push(&pq, tmp);
        } else {
            if(pq_isEmpty(&pq))
                puts("HORE");
            else {
                printf("%u\n", pq_top(&pq).id);
                pq_pop(&pq);
            }
        }
    }
    return 0;
}