#include <stdlib.h>

void fill(int *vector, int size, int value) {
    for(int i = 0; i < size; i++)
        vector[i] = value;
}

int find(int *vector, int size, int value) {
    for(int i = 0; i < size; i++) {
        if(vector[i] == value) {
            return i;
        }
    }
    return -1;
}