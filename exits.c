#include "main.h"

/**
 **_strncpy - to copy a string
 *@dest: Destination string to be copied to
 *@src: a source string
 *@n: an amount of characters to be copied
 *Return: concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int w;
	char *s = dest;

	for (w = 0; src[w] != '\0' && w < n - 1; w++)
	{
	dest[w] = src[w];
	}
	if (w < n)
	{
	int y;

	for (y = w; y < n; y++)
		{
		dest[y] = '\0';
		}
	}
	return (s);
}

/**
 **_strncat - to concate two strings
 *@dest: first string
 *@src: second string
 *@n: An amount of bytes to be maximally used
 *Return: to concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int a, b;
	char *s = dest;

	for (a = 0; dest[a] != '\0'; a++)
	{
	}

	for (b = 0; src[b] != '\0' && b < n; b++)
	{
		dest[a] = src[b];
		a++;
	}

	if (b < n)
	{
		dest[a] = '\0';
	}

	return (s);
}

/**
 **_strchr - to locate a character in a string
 *@s: a string to be parsed
 *@c: the char to look for
 *Return: (s) the pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	for (; *s != '\0'; s++)
	{
		if (*s == c)
		{
			return (s);
		}
	}

	return (NULL);
}
