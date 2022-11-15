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

/**
 * *_strcpy - copy string pointed to by src to string pointed to by dest
 * @dest: destination
 * @src: string to copy
 * Return: a pointer to the destination
 */

char *_strcpy(char *dest, const char *src)
{
    int i;
    if (!src)
        dest = NULL;

    for (i = 0; src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return (dest);
}