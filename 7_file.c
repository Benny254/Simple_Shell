#include "main.h"

/**
 * cpy_str - copy a string
 * @dest: destination
 * @src: source
 * Return: the pointer to destination
 */
char *cpy_str(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * dupstr - duplicate string
 * @str: string to be duplicated
 * Return: pointer to duplicated string
 */
char *dupstr(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * print_str - print an input string
 * @str: string to be printed
 * Return: Null
 */
void print_str(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		printch(str[i]);
		i++;
	}
}

/**
 * printch - write the character c to stdout
 * @c: The char to be printed
 * Return: On success 1.
 */
int printch(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
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
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
