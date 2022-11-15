#include "main.h"

/**
 * _strlen - calculate length of a string
 * @s: input string
 * Return: length of a string or 0 if string is NULL
 */

int _strlen(const char *s)
{
    int l = 0;

    if (!s)
        return (l);

    while (*s != '\0')
    {
        s++;
        l++;
    }
    return (l);
}