#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#define ceq(x, y) strcmp(x, y) == 0

typedef struct _LinkedListNode {
    char string[101];
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

bool isEmpty(LinkedList List) {
    return List.head == NULL;
}

void pushBack(LinkedList *List, char * string) {
    LinkedListNode * newLinkedListNode = (LinkedListNode *) malloc(sizeof(LinkedListNode));
    if(newLinkedListNode) {
        List->size++;
        strcpy(newLinkedListNode->string, string);
        newLinkedListNode->next = NULL;

        if(isEmpty(*List))
            List->head = newLinkedListNode;
        else {
            LinkedListNode * tmp = List->head;
            while(tmp->next != NULL)
                tmp = tmp->next;
            tmp->next = newLinkedListNode;
        }
    }
}

void pushFront(LinkedList *List, char * string) {
    LinkedListNode * newLinkedListNode = (LinkedListNode *) malloc(sizeof(LinkedListNode));
    if(newLinkedListNode) {
        List->size++;
        strcpy(newLinkedListNode->string, string);

        if(isEmpty(*List))
            newLinkedListNode->next = NULL;
        else
            newLinkedListNode->next = List->head;
        List->head = newLinkedListNode;
    }
}

void insertAt(LinkedList *List, char * string, unsigned index) {
    if(index == 0)
        pushFront(List, string);
    else if(index >= List->size)
        pushBack(List, string);
    else {
        LinkedListNode * newLinkedListNode = (LinkedListNode *) malloc(sizeof(LinkedListNode));
        if(newLinkedListNode) {
            strcpy(newLinkedListNode->string, string);
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

char * back(LinkedList List) {
    if(!isEmpty(List)) {
        LinkedListNode * tmp = List.head;
        while(tmp->next != NULL)
            tmp = tmp->next;
        return tmp->string;
    }
    return "\0";
} 

char * front(LinkedList List) {
    if(!isEmpty(List))
        return List.head->string;
    else return "\0";
}

char * getAt(LinkedList List, unsigned index) {
    if(!isEmpty(List)) {
        LinkedListNode * tmp = List.head;
        unsigned i = 0;
        while(tmp->next != NULL && i < index) {
            i++;
            tmp = tmp->next;
        }
        return tmp->string;
    }
    return "\0";
}

void popBack(LinkedList * List) {
    if(!isEmpty(*List)) {
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

void popFront(LinkedList * List) {
    if(!isEmpty(*List)) {
        LinkedListNode * front = List->head;
        List->head = List->head->next;
        List->size--;
        free(front);
    }
}

void removeVal(LinkedList * List, char * string) {
    if(!isEmpty(*List)) {
        LinkedListNode * tmp = List->head, *prev;

        if(ceq(tmp->string, string)) {
            popFront(List);
            return;
        }

        while(tmp != NULL && !ceq(tmp->string, string)) {
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

void printElement(char *elem) { printf("%s", elem); }

void reverseEach(char *elem) {
    elem = strrev(elem);
}

void forEachElement(LinkedList * List, void (*func)(char *)) {
    LinkedListNode * tmp = List->head, *prev = NULL;
    while(tmp != NULL) {
        LinkedListNode * next = tmp->next;
        (*func)(tmp->string);
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
    pushBack(&ll, "Zydhan");
    pushFront(&ll, "Gaming");
    pushBack(&ll, "Mobile Legend");
    pushFront(&ll, "PES 2020");
    popBack(&ll);
    insertAt(&ll, "GTA V", 8);
    printf("front : %s, back : %s, get(1) : %s, get(4) : %s\n", front(ll), back(ll), getAt(ll, 1), getAt(ll, 4));
    forEachElement(&ll, printElement);
    forEachElement(&ll, reverseEach);
    forEachElement(&ll, printElement);
    return 0;
}