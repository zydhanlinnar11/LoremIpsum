#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct dynamicarr_t {
    char **_arr;
    unsigned _size, _capacity;
} DynamicArray;

bool initDArray(DynamicArray *dArray) {
    dArray->_capacity = 1;
    dArray->_size = 0;
    dArray->_arr = (char **) malloc(sizeof(char *));
    dArray->_arr[0] = (char *) malloc(101 * sizeof(char));
}

bool dArray_isEmpty(DynamicArray *darray) {
    return (darray->_size == 0);
}

void dArray_pushBack(DynamicArray *darray, char * string) {
    if (darray->_size + 1 > darray->_capacity) {
        unsigned it;
        darray->_capacity *= 2;
        char **newArr = (char **) malloc(sizeof(char *) * darray->_capacity);

        for (it=0; it < darray->_size; ++it) {
            newArr[it] = (char *) malloc(101 * sizeof(char));
            strcpy(newArr[it], darray->_arr[it]);
        }
        
        char **oldArray = darray->_arr;
        darray->_arr = newArr;
        free(oldArray);
    }
    darray->_arr[darray->_size] = (char *) malloc(101 * sizeof(char));
    strcpy(darray->_arr[darray->_size++], string);
}

void dArray_popBack(DynamicArray *darray) {
    if (!dArray_isEmpty(darray)) darray->_size--;
    else return;
}

char * dArray_back(DynamicArray *darray) {
    if (!dArray_isEmpty(darray))
        return darray->_arr[darray->_size-1];
    else return "\0";
}

char * dArray_front(DynamicArray *darray) {
    if (!dArray_isEmpty(darray))
        return darray->_arr[0];
    else return "\0";
}

void dArray_setAt( DynamicArray *darray, unsigned index, char * string) {
    if (!dArray_isEmpty(darray)) {
        if (index >= darray->_size)
            strcpy(darray->_arr[darray->_size - 1], string);
        else
            strcpy(darray->_arr[index], string);
    }
}

char * dArray_getAt(DynamicArray *darray, unsigned index) {
    if (!dArray_isEmpty(darray)) {
        if (index >= darray->_size)
            return darray->_arr[darray->_size-1];
        else
            return darray->_arr[index];
    } else return "\0";
}

void dArray_insertAt(DynamicArray *darray, unsigned index, char * string) {
    if(index >= darray->_size)
        dArray_pushBack(darray, string);
    else {
        char **curr = darray->_arr;
        if(darray->_size + 1 > darray->_capacity)
            darray->_capacity *= 2;
        char **new = (char **) malloc(darray->_capacity * sizeof(char *));
        unsigned i = 0;
        if(index == 0) {
            for(; i < darray->_size; i++){
                new[i + 1] = (char *) malloc(101 * sizeof(char));
                strcpy(new[i + 1], curr[i]);
            }
            new[0] = (char *) malloc(101 * sizeof(char));
            strcpy(new[0], string);
        } else {
            for(; i < index; i++){
                new[i] = (char *) malloc(101 * sizeof(char));
                new[i] = curr[i];
            }
            new[index] = (char *) malloc(101 * sizeof(char));
            new[index] = string;
            for(i = index; i < darray->_size; i++){
                new[i + 1] = (char *) malloc(101 * sizeof(char));
                new[i + 1] = curr[i];
            }
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
        char **curr = darray->_arr;
        char **new = (char **) malloc(darray->_capacity * sizeof(char *));
        unsigned i = 0;
        if(index == 0) {
            for(; i < (darray->_size - 1); i++){
                new[i] = (char *) malloc(101 * sizeof(char));
                strcpy(new[i], curr[i + 1]);
            }
        } else {
            for(; i < index; i++){
                new[i] = (char *) malloc(101 * sizeof(char));
                new[i] = curr[i];
            }
            for(i = index; i < (darray->_size - 1); i++){
                new[i] = (char *) malloc(101 * sizeof(char));
                new[i] = curr[i + 1];
            }
        }

        darray->_size--;
        darray->_arr = new;
        free(curr);
    }
}

int main() {
    DynamicArray arr;
    initDArray(&arr);

    dArray_pushBack(&arr, "Zydhan");
    dArray_pushBack(&arr, "Mobile Legend");
    dArray_pushBack(&arr, "GTA V");
    dArray_pushBack(&arr, "DELL E6230");
    dArray_insertAt(&arr, 3, "Gaming");
    dArray_removeAt(&arr, 1);
    printf("front : %s, back : %s, get(1) : %s, get(4) : %s\n", dArray_front(&arr), dArray_back(&arr), dArray_getAt(&arr, 1), dArray_getAt(&arr, 4));
    dArray_popBack(&arr);
    dArray_pushBack(&arr, "Redmi 6");
    dArray_pushBack(&arr, "PUBG Lite");
    dArray_setAt(&arr, 5, "PES 2020");
    printf("front : %s, back : %s, get(1) : %s, get(4) : %s\n", dArray_front(&arr), dArray_back(&arr), dArray_getAt(&arr, 1), dArray_getAt(&arr, 4));
    return 0;
}