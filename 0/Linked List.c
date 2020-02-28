#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct _LinkedListNode {
    int value;
    struct _LinkedListNode * next;
} LinkedListNode;

typedef struct list {
    LinkedListNode * head;
    unsigned size;
} LinkedList;

bool initLinkedList(LinkedList * List) {
    List->head = NULL;
    List->size = 0;
}

bool ll_isEmpty(LinkedList List) {
    return List.head == NULL;
}

void ll_pushBack(LinkedList *List, int val) {
    LinkedListNode * newLinkedListNode = (LinkedListNode *) malloc(sizeof(LinkedListNode));
    if(newLinkedListNode) {
        List->size++;
        newLinkedListNode->value = val;
        newLinkedListNode->next = NULL;

        if(ll_isEmpty(*List))
            List->head = newLinkedListNode;
        else {
            LinkedListNode * tmp = List->head;
            while(tmp->next != NULL)
                tmp = tmp->next;
            tmp->next = newLinkedListNode;
        }
    }
}

void ll_pushFront(LinkedList *List, int val) {
    LinkedListNode * newLinkedListNode = (LinkedListNode *) malloc(sizeof(LinkedListNode));
    if(newLinkedListNode) {
        List->size++;
        newLinkedListNode->value = val;

        if(ll_isEmpty(*List))
            newLinkedListNode->next = NULL;
        else
            newLinkedListNode->next = List->head;
        List->head = newLinkedListNode;
    }
}

void ll_insertAt(LinkedList *List, int val, unsigned index) {
    if(index == 0)
        ll_pushFront(List, val);
    else if(index >= List->size)
        ll_pushBack(List, val);
    else {
        LinkedListNode * newLinkedListNode = (LinkedListNode *) malloc(sizeof(LinkedListNode));
        if(newLinkedListNode) {
            newLinkedListNode->value = val;
            List->size++;
            LinkedListNode * tmp = List->head;
            unsigned i = 0;
            while(i < (index - 1) && tmp->next != NULL) {
                i++;
                tmp = tmp->next;
            }
            newLinkedListNode->next = tmp->next;
            tmp->next = newLinkedListNode;
        }
    }
}

int ll_back(LinkedList List) {
    if(!ll_isEmpty(List)) {
        LinkedListNode * tmp = List.head;
        while(tmp->next != NULL)
            tmp = tmp->next;
        return tmp->value;
    }
    return INT_MIN;
} 

int ll_front(LinkedList List) {
    if(!ll_isEmpty(List))
        return List.head->value;
    else return INT_MIN;
}

int ll_getAt(LinkedList List, unsigned index) {
    if(!ll_isEmpty(List)) {
        LinkedListNode * tmp = List.head;
        unsigned i = 0;
        while(tmp->next != NULL && i < index) {
            i++;
            tmp = tmp->next;
        }
        return tmp->value;
    }
    return 0;
}

void ll_popBack(LinkedList * List) {
    if(!ll_isEmpty(*List)) {
        LinkedListNode * currPtr = List->head;
        if(List->size-- == 1) {
            free(currPtr);
            List->head = NULL;
            return;
        }

        LinkedListNode * nextPtr = List->head->next;
        while(nextPtr->next != NULL) {
            currPtr = nextPtr;
            nextPtr = nextPtr->next;
        }
        currPtr->next = NULL;
        free(nextPtr);
    }
}

void ll_popFront(LinkedList * List) {
    if(!ll_isEmpty(*List)) {
        LinkedListNode * front = List->head;
        List->head = List->head->next;
        List->size--;
        free(front);
    }
}

void ll_removeVal(LinkedList * List, int val) {
    if(!ll_isEmpty(*List)) {
        LinkedListNode * tmp = List->head, *prev;

        if(tmp->value == val) {
            ll_popFront(List);
            return;
        }

        while(tmp != NULL && tmp->value != val) {
            prev = tmp;
            tmp = tmp->next;
        }

        if(tmp == NULL)
            return;
        prev->next = tmp->next;
        free(tmp);
        List->size--;
    }
}

void printElement(int *elem) { printf("%d", *elem); }

void multiply2(int *elem) { *elem <<= 1; }

void sumDigit(int *elem) {
    int sum = 0;
    while((*elem) > 0) {
        sum += ((*elem) % 10);
        (*elem) /= 10;
    }
    *elem = sum;
}

void reverseEach(int *elem) {
    int tmp = 0;
    while(*elem > 0) {
        tmp = (tmp * 10) + (*elem % 10);
        *elem /= 10;
    }
    *elem = tmp;
}

void forEachElement(LinkedList * List, void (*func)(int *)) {
    LinkedListNode * tmp = List->head, *prev = NULL;
    while(tmp != NULL) {
        LinkedListNode * next = tmp->next;
        (*func)(&tmp->value);
        if((*func) == printElement && next != NULL)
            printf(" -> ");
        tmp = next;
    }
    if((*func) == printElement)
        printf("\n");
}

int main() {
    LinkedList ll;
    initLinkedList(&ll);
    short i;
    for(i = 1; i <= 10; i++)
        ll_pushBack(&ll, i);
    forEachElement(&ll, printElement);
    forEachElement(&ll, multiply2);
    forEachElement(&ll, printElement);
    forEachElement(&ll, sumDigit);
    forEachElement(&ll, printElement);
    forEachElement(&ll, reverseEach);
    forEachElement(&ll, printElement);
    return 0;
}