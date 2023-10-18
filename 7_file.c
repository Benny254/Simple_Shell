#include "main.h"
#define BUF_FLUSH 0x8000
#define WRITE_BUF_SIZE 1024

/**
 * cpy_str - copy a string
 * @d: destination
 * @s: source
 * Return: the pointer to destination
 */
char *cpy_str(char *dest, const char *src)
{
	int pt;

	for (pt = 0; src[pt]; pt++) {
	dest[pt] = src[pt];
	}
	dest[pt] = '\0';

	return dest;
}

/**
 * dupstr - duplicate string
 * @st: string to be duplicated
 * Return: pointer to duplicated string
 */
char *dupstr(const char *st)
{
	int len = 0;
	char *pt;

	if (st == NULL)
		return (NULL);
	while (*st++)
		len++;
	pt = malloc(sizeof(char) * (len + 1));
	if (!pt)
		return (NULL);
	for (len++; len--;)
		pt[len] = *--st;
	return (pt);
}

/**
 * print_str - print an input string
 * @s: string to be printed
 * Return: Null
 */
void print_str(char *str, char *s)
{
	if (!s)
		return;

	int len = 0;

	while (s[len] != '\0')
	{
		eprintch(str[len]);
		len++;
	}
}

/**
 * printch - write the character c to stdout
 * @c: The char to be printed
 * Return: On success 1.
 */
int printch(char c)
{
	static int a;
	static char buff[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(1, buff, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buff[a++] = c;
	return (1);
}

/**
 * comp_str - perform lexicogarphic comparison of two strings
 * @s1: first string
 * @s2: second string
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int comp_str(char *s1, char *s2)
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
