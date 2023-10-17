#include "main.h"

/**
 * _strcpy - to copy a string
 * @dest:  Destination
 * @src: a source
 *
 * Return: the pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int x;

	if (dest == src || src == 0)
	return (dest);
	for (x = 0; src[x]; x++)
	{
	dest[x] = src[x];
	}
	dest[x] = 0;
	return (dest);
}

/**
 * _strdup - to duplicate a string
 * @str: a string to be duplicated
 *
 * Return: the pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int str_length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		str_length++;
	ret = malloc(sizeof(char) * (str_length + 1));
	if (!ret)
		return (NULL);
	for (str_length++; str_length--;)
		ret[str_length] = *--str;
	return (ret);
}

/**
 * _puts - to print an input string
 * @str: a string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	if (!str)
		return;

	int x = 0;

	while (str[x] != '\0')
	{
		_putchar(str[x]);
		x++;
	}
}

/**
 * _putchar - to write the character c to stdout
 * @c: The char to be printed
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(1, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;
	return (1);
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
