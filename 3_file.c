#include "main.h"

/**
 * eprintch - to write the char to stderr
 * @ch: the char to be printed
 * Return: On success 1
 */
int eprintch(char ch)
{
	static int l;
	static char b[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || l >= WRITE_BUF_SIZE)
	{
		write(2, b, l);
		l = 0;
	}
	if (ch != BUF_FLUSH)
		b[l++] = ch;
	return (1);
}

/**
 * write_ch - to write character to a given fd
 * @ch: a given character
 * @fd: the file descriptor
 * Return: On success 1
 */
int write_ch(char ch, int fd)
{
	static int i;
	static char b[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, b, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		b[i++] = ch;
	return (1);
}

/**
 * pfd_input - to print an input string
 * @s: a given string
 * @fd: the file descriptor
 * Return: the number of chars put
 */
int pfd_input(char *s, int fd)
{
	int l = 0;

	if (!s)
		return (0);
	while (*s)
	{
		l += write_ch(*s++, fd);
	}
	return (l);
}

/**
 * cp_char - to duplicate characters
 * @p_str: the PATH string
 * @a: the starting index
 * @b: the stopping index
 * Return: the pointer to new buffer
 */
char *cp_char(char *p_str, int a, int b)
{
	static char buff[1024];
	int l = 0, m = 0;

	for (m = 0, l = a; l < b; l++)
		if (p_str[l] != ':')
			buff[m++] = p_str[l];
	buff[m] = 0;
	return (buff);
}

/**
 * free_p - to free a pointer and NULLs address
 * @p: an address of pointer to free
 * Return: 1 if success
 */
int free_p(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
