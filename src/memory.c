/**
 * @file memory.c
 * @author Ian Duncan (dr8co@duck.com)
 * @brief source file for memory management and related functions
 * @version 3.0
 * @date 2023-02-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "main.h"
#include <stdlib.h>

/**
 * @brief reallocates a memory block using malloc and free.
 * @param ptr pointer to previously allocated memory.
 * @param new_size size of newly allocated space.
 *
 * @return a pointer to newly allocated memory, or NULL if failure.
 */
void *re_alloc(void *ptr, unsigned int new_size) {
    char *p;
    unsigned int i, max = new_size;
    unsigned int old_size = sizeof(ptr);
    char *old_ptr = ptr;

    if (ptr == NULL) {
        p = malloc(new_size);
        return (p);
    } else if (new_size == 0) {
        free(ptr);
        return (NULL);
    } else if (new_size == old_size)
        return (ptr);

    p = malloc(new_size);
    if (p == NULL)
        return (NULL);

    if (new_size > old_size)
        max = old_size;

    for (i = 0; i < max; i++)
        p[i] = old_ptr[i];

    free(ptr);
    return (p);
}

/**
 * @brief fills memory with a constant byte.
 * @param s - the memory space to be filled.
 * @param b - the byte to fill with.
 * @param n - the number of spaces to fill.
 *
 * @return a pointer to the filled memory area.
 */
char *mem_set(char *s, char b, unsigned int n) {
    unsigned int i;

    for (i = 0; i < n; ++i) {
        *(s + i) = b;
    }
    return (s);
}
