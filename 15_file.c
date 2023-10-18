#include "main.h"

/**
 * infoclr - initialize sh_info_t struct
 * @sh_info: struct address
 */
void infoclr(sh_info_t *sh_info)
{
	sh_info->arg = NULL;
	sh_info->path = NULL;
	sh_info->argv = NULL;
	sh_info->argc = 0;
}

/**
 **cppy_str - copy a string
 *@dest: Destination
 *@src: source string
 *@ch: amount of characters to be copied
 *Return: string
 */
char *cppy_str(char *dest, char *src, int ch)
{
	int w;
	char *s = dest;

	for (w = 0; src[w] != '\0' && w < ch - 1; w++)
	{
	dest[w] = src[w];
	}
	if (w < ch)
	{
	int y;

	for (y = w; y < ch; y++)
		{
		dest[y] = '\0';
		}
	}
	return (s);
}

/**
 **concat_str - concate two strings
 *@dest: first string
 *@src: second string
 *@by: amount of bytes to be maximally used
 *Return: concatenated string
 */
char *concat_str(char *dest, char *src, int by)
{
	int a, b;
	char *s = dest;

	for (a = 0; dest[a] != '\0'; a++)
	{
	}

	for (b = 0; src[b] != '\0' && b < by; b++)
	{
		dest[a] = src[b];
		a++;
	}

	if (b < by)
	{
		dest[a] = '\0';
	}

	return (s);
}

/**
 **loc_ch - locate a character in a string
 *@s: a string to be parsed
 *@ch: the char to look for
 *Return: (s)
 */
char *loc_ch(char *s, char ch)
{
	for (; *s != '\0'; s++)
	{
		if (*s == ch)
		{
			return (s);
		}
	}

	return (NULL);
}
