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

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: the difference of s1 and s2
 */
int _strcmp(const char *s1, const char *s2)
{
    int i = 0;

    while (*(s1 + i) && *(s2 + i) && (*(s1 + i) == *(s2 + i)))
        i++;
    return (*(s1 + i) - *(s2 + i));
}

/**
 * _strcat - appends src string to the dest string
 * @dest: string to append by src
 * @src: string to append to dest
 *
 * Return: pointer to the resulting string dest,
 * or NULL if both strings are not present or NULL.
 */
char *_strcat(char *dest, char *src)
{
    int i, j;

    if (!dest && !src){
        return NULL;
    } else if (!dest){
        return src;
    } else if (!src){
        return dest;
    }
    i = j = 0;
    while (*(dest + i))
        i++;
    while ((*(dest + i) = *(src + j)))
    {
        i++;
        j++;
    }
    return (dest);
}

/**
 * _memset - fills memory with a constant byte
 * @s: memory space to be filled
 * @b: byte to fill with
 * @n: number of spaces to fill
 *
 * Return: pointer to memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
    unsigned int i;

    for (i = 0; i < n; i++)
    {
        *(s + i) = b;
    }
    return (s);
}
