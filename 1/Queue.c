#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct _QueueNode {
    int value;
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

void q_enqueue(queue * q, int val) {
    QueueNode * newQueueNode = (QueueNode *) malloc(sizeof(QueueNode));
    if(newQueueNode) {
        newQueueNode->value = val;
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

int q_front(queue * q) {
    if(!q_isEmpty(q))
        return q->front->value;
    else return INT_MIN;
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
    printf("front : %d\n", q_front(&q));
    q_dequeue(&q);
    printf("Size : %u\n", q_getSize(&q));
    q_enqueue(&q, 4);
    printf("front : %d\n", q_front(&q));
    q_dequeue(&q);
    q_dequeue(&q);
    printf("Size : %u\n", q_getSize(&q));
    q_enqueue(&q, 0);
    q_enqueue(&q, 4);
    q_enqueue(&q, 5);
    q_enqueue(&q, 1);
    printf("front : %d\n", q_front(&q));
    q_dequeue(&q);
    printf("Size : %u\n", q_getSize(&q));
    printf("front : %d\n", q_front(&q));
    q_dequeue(&q);
    printf("Size : %u\n", q_getSize(&q));
    printf("front : %d\n", q_front(&q));
    q_dequeue(&q);
    printf("Size : %u\n", q_getSize(&q));
    return 0;
}