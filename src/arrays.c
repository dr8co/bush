#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * @brief get the number of items in an array.
 * @param arr the array to evaluate.
 * @return the number of items in the array.
 */
int get_size(char **arr) {
    int size = 0;
    for (int i = 0; arr[i]; ++i) {
        ++size;
    }
    return size;
}

/**
 * @brief remove an item from an array (in place).
 * @param arr the array to evaluate.
 * @param index the index of the item to be removed from the array.
 * @return the new array with the element removed.
 */
char **remove_element(char **arr, int index) {
    int size = get_size(arr);

    if (index >= size || index < 0) {
        fprintf(stderr, "Operation not possible: index out of range.");
        return arr;
    } else {
        for (int i = index; i < size - 1; ++i) {
            arr[i] = arr[i + 1];
        }
    }
    arr[size - 1] = NULL;
    return arr;
}

/**
 * @brief merge two arrays.
 * @param arr1 the parent array.
 * @param arr2 the child array to be inserted into the parent array.
 * @param index the index in parent array at which the child array is to be inserted.
 * @return the merged array.
 */
char **merge_arrays(char **arr1, char **arr2, int index) {
    int size1 = get_size(arr1);
    int size2 = get_size(arr2);

    int i = 0, j = 0, pos = index;
    char **arr3 = (char **) malloc(sizeof(arr1) + sizeof(arr2) + 100);

    if (index > size1 || index <= -2) {
        fprintf(stderr, "Invalid index");
        exit(-1);
    } else {
        for (; i <= index; ++i) {
            arr3[i] = arr1[i];
        }
        for (; j < size2; ++j) {
            arr3[i] = arr2[j];
            ++i;
        }
        ++pos;
        for (int k = index + size2 + 1; k < size2 + size1 && arr1[pos]; ++k) {
            arr3[k] = arr1[pos];
            ++pos;
        }
    }

    return arr3;
}
