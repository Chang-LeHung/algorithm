#include <cstdio>
#include <cstring>
#include <stdlib.h>

#define True 1
#define False 0
#define NUM 9

void swap(int * array, int idx1, int idx2) {
    /* 交换数组的两个元素 */
    int t = array[idx1];
    array[idx1] = array[idx2];
    array[idx2] = t;
}

void down(int * array, int length, int start, int big=False) {
    while(start < length) {
        int left_child = 2 * start + 1;
        int right_child = 2 * start + 2;
        int idx = left_child;
        if (left_child > length - 1)
            break;
        if(right_child < length) {
            if (!big) {
                if(array[right_child] < array[left_child])
                    idx = right_child;
            } else {
                if(array[right_child] > array[left_child])
                    idx = right_child;
            }
        }
        if(!big) {
            if(array[start] > array[idx]){
                swap(array, idx, start);
                start = idx;
            } else{
                break;
            }
        } else {
            if(array[start] < array[idx]){
                swap(array, idx, start);
                start = idx;
            } else{
                break;
            }
        }
    }
}

void heapify(int * array, int length, int start=-2, int big=True) {

    if(start == -1)
        return;
    if (start == -2) {
        start = (length - 2) / 2;
    }
    down(array, length, start, big);
    heapify(array, length, start - 1, big);
}


void heap_sort(int * array, int length, bool reverse=False) {
    for(int i = length - 1; i >=0; i--) {
        swap(array, i, 0);
        down(array, i, 0, !reverse);
    }
}

int main() {
    int data[NUM] = {0, 7, 3, 5, 1, 6, 2, 4, 8};
    heapify(data, NUM);
    for(int i=0; i < NUM; i++) {
        printf("%d ", data[i]);
    }
    heap_sort(data, NUM);
    printf("\nAfter sorted !!!\n");
    for(int i=0; i < NUM; i++) {
        printf("%d ", data[i]);
    }
    return 0;
}
