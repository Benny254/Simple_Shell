#include "main.h"

/**
 * _strlen - to return the length of a string
 * @s: a string whose length is to be checked
 *
 * Return: an integer length of string
 */
int _strlen(char *s)
{
	int y;

	if (!s)
		return (0);

	for (y = 0; *s != '\0'; y++)
		s++;

	return (y);
}

/**
 * _strcmp - to perform lexicogarphic comparison of two strangs.
 * @s1: first strang
 * @s2: second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	for (; *s1 && *s2; s1++, s2++)
	{
	if (*s1 != *s2)
	return (*s1 - *s2);
	}

	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - to check if needle starts with haystack
 * @haystack: the string to be searched
 * @needle: substring to find
 *
 * Return: an address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - to conca two strings
 * @dest: Destination buffer
 * @src: a source buffer
 *
 * Return: the pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	for (; *dest; dest++)

	for (; *src; src++, dest++)
	{
	*dest = *src;
	}

	*dest = *src;

	return (ret);
}
