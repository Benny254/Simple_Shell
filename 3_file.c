#include "main.h"

/**
 * eprintch - to write the char to stderr
 * @c: the char to be printed
 * Return: On success 1
 */
int eprintch(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * write_ch - to write character to a given fd
 * @c: a given character
 * @fd: the file descriptor
 * Return: On success 1
 */
int write_ch(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * pfd_input - to print an input string
 * @str: a given string
 * @fd: the file descriptor
 * Return: number of chars put
 */
int pfd_input(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += write_ch(*str++, fd);
	}
	return (i);
}

/**
 * cp_char - to duplicate characters
 * @pathstr: the PATH string
 * @start: the starting index
 * @stop: the stopping index
 * Return: the pointer to new buffer
 */
char *cp_char(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * free_p - to free a pointer and NULLs address
 * @ptr: an address of pointer to free
 * Return: 1 if success
 */
int free_p(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
