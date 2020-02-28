#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct dynamicarr_t {
    int *_arr;
    unsigned _size, _capacity;
} DynamicArray;

bool initDArray(DynamicArray *dArray) {
    dArray->_capacity = 1;
    dArray->_size = 0;
    dArray->_arr = (int *) malloc(sizeof(int));
}

bool dArray_isEmpty(DynamicArray *darray) {
    return (darray->_size == 0);
}

void dArray_pushBack(DynamicArray *darray, int value) {
    if (darray->_size + 1 > darray->_capacity) {
        unsigned it;
        darray->_capacity *= 2;
        int *newArr = (int*) malloc(sizeof(int) * darray->_capacity);

        for (it=0; it < darray->_size; ++it)
            newArr[it] = darray->_arr[it];
        
        int *oldArray = darray->_arr;
        darray->_arr = newArr;
        free(oldArray);
    }
    darray->_arr[darray->_size++] = value;
}

void dArray_popBack(DynamicArray *darray) {
    if (!dArray_isEmpty(darray)) darray->_size--;
    else return;
}

int dArray_back(DynamicArray *darray) {
    if (!dArray_isEmpty(darray))
        return darray->_arr[darray->_size-1];
    else return 0;
}

int dArray_front(DynamicArray *darray) {
    if (!dArray_isEmpty(darray))
        return darray->_arr[0];
    else return 0;
}

void dArray_setAt( DynamicArray *darray, unsigned index, int value) {
    if (!dArray_isEmpty(darray)) {
        if (index >= darray->_size)
            darray->_arr[darray->_size-1] = value;
        else
            darray->_arr[index] = value;
    }
}

int dArray_getAt(DynamicArray *darray, unsigned index) {
    if (!dArray_isEmpty(darray)) {
        if (index >= darray->_size)
            return darray->_arr[darray->_size-1];
        else
            return darray->_arr[index];
    }
}

void dArray_insertAt(DynamicArray *darray, unsigned index, int value) {
    if(index >= darray->_size)
        dArray_pushBack(darray, value);
    else {
        int * curr = darray->_arr;
        if(darray->_size + 1 > darray->_capacity)
            darray->_capacity *= 2;
        int *new = (int *) malloc(darray->_capacity * sizeof(int));
        unsigned i = 0;
        if(index == 0) {
            new[0] = value;
            for(; i < darray->_size; i++)
                new[i + 1] = curr[i];
        } else {
            for(; i < index; i++)
                new[i] = curr[i];
            new[index] = value;
            for(i = index; i < darray->_size; i++)
                new[i + 1] = curr[i];
        }

        darray->_size++;
        darray->_arr = new;
        free(curr);
    }
}

void dArray_removeAt(DynamicArray *darray, unsigned index) {
    if(index >= darray->_size)
        dArray_popBack(darray);
    else {
        int * curr = darray->_arr;
        int *new = (int *) malloc(darray->_capacity * sizeof(int));
        unsigned i = 0;
        if(index == 0) {
            for(; i < (darray->_size - 1); i++)
                new[i] = curr[i + 1];
        } else {
            for(; i < index; i++)
                new[i] = curr[i];
            for(i = index; i < (darray->_size - 1); i++)
                new[i] = curr[i + 1];
        }

        darray->_size--;
        darray->_arr = new;
        free(curr);
    }
}

int main() {
    DynamicArray arr;
    initDArray(&arr);

    dArray_pushBack(&arr, 5);
    dArray_pushBack(&arr, 2);
    dArray_pushBack(&arr, -10);
    dArray_pushBack(&arr, 99);
    dArray_insertAt(&arr, 3, 77);
    dArray_removeAt(&arr, 100);
    printf("front : %d, back : %d, get(1) : %d, get(4) : %d\n", dArray_front(&arr), dArray_back(&arr), dArray_getAt(&arr, 1), dArray_getAt(&arr, 4));
    dArray_popBack(&arr);
    dArray_pushBack(&arr, -10);
    dArray_pushBack(&arr, 99);
    dArray_setAt(&arr, 1, 3);
    printf("front : %d, back : %d, get(1) : %d, get(4) : %d\n", dArray_front(&arr), dArray_back(&arr), dArray_getAt(&arr, 1), dArray_getAt(&arr, 4));
    return 0;
}