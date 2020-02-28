#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct _QueueNode {
    char string[101];
    struct _QueueNode * next;
} QueueNode;

typedef struct _queue {
    unsigned size;
    QueueNode * front, * rear;
} queue;

void initQueue(queue * q) {
    q->size = 0;
    q->front = q->rear = NULL;
}

bool q_isEmpty(queue * q) { return (q->front == NULL && q->rear == NULL); }

unsigned q_getSize(queue * q) { return q->size; }

void q_enqueue(queue * q, char * str) {
    QueueNode * newQueueNode = (QueueNode *) malloc(sizeof(QueueNode));
    if(newQueueNode) {
        strcpy(newQueueNode->string, str);
        newQueueNode->next = NULL;
        
        if(q_isEmpty(q))
            q->front = q->rear = newQueueNode;
        else {
            q->rear->next = newQueueNode;
            q->rear = newQueueNode;
        }
        q->size++;
    } else puts("Memory penuh slur.");
}

char * q_front(queue * q) {
    if(!q_isEmpty(q))
        return q->front->string;
    else return "NULL";
}

void q_dequeue(queue * q) {
    if(!q_isEmpty(q)) {
        QueueNode * tmp = q->front;
        if(q->size-- == 1)
            q->front = q->rear = NULL;
        else q->front = q->front->next;

        free(tmp);
    } else puts("Udah habis slur");
}

int main() {
    queue q;
    initQueue(&q);
    printf("front : %s\n", q_front(&q));
    q_dequeue(&q);
    printf("Size : %u\n", q_getSize(&q));
    q_enqueue(&q, "4");
    printf("front : %s\n", q_front(&q));
    q_dequeue(&q);
    q_dequeue(&q);
    printf("Size : %u\n", q_getSize(&q));
    q_enqueue(&q, "0");
    q_enqueue(&q, "4");
    q_enqueue(&q, "5");
    q_enqueue(&q, "1");
    printf("front : %s\n", q_front(&q));
    q_dequeue(&q);
    printf("Size : %u\n", q_getSize(&q));
    printf("front : %s\n", q_front(&q));
    q_dequeue(&q);
    printf("Size : %u\n", q_getSize(&q));
    printf("front : %s\n", q_front(&q));
    q_dequeue(&q);
    printf("Size : %u\n", q_getSize(&q));
    return 0;
}