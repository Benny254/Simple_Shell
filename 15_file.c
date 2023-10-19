#include "main.h"

/**
 * infoclr - initialize sh_info_t struct
 * @info: struct address
 */
void infoclr(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 **cppy_str - copy a string
 *@dest: Destination
 *@src: source string
 *@n: amount of characters to be copied
 *Return: string
 */
char *cppy_str(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * *concat_str - concate two strings
 * @dest: first string
 * @src: second string
 * @n: amount of bytes to be maximally used
 * Return: concatenated string
 */
char *concat_str(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **loc_ch - locate a character in a string
 *@s: a string to be parsed
 *@c: the char to look for
 *Return: (s)
 */
char *loc_ch(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
