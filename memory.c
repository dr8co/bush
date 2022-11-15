#include "main.h"
#include <stdlib.h>

/**
 * _realloc - reallocates a memory block using malloc and free.
 * @ptr: pointer to previously allocated memory
 * @new_size: size of newly allocated space
 *
 * Return: pointer to newly allocated memory, or NULL if failure
 */
void *_realloc(void *ptr, unsigned int new_size)
{
    char *p;
    unsigned int i, max = new_size;
    unsigned int old_size = sizeof(ptr);
    char *old_ptr = ptr;

    if (ptr == NULL)
    {
        p = malloc(new_size);
        return (p);
    }
    else if (new_size == 0)
    {
        free(ptr);
        return (NULL);
    }
    else if (new_size == old_size)
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
