#include "main.h"

/**
 * string_convert - to convert string representation
 * of integer to integer value
 * @str: the given string
 * Return: the converted number otherwise -1 on error
 */
int string_convert(char *str)
{
	int l = 0;
	unsigned long int num = 0;

	if (*str == '+')
		str++;
	for (l = 0;  str[l] != '\0'; l++)
	{
		if (str[l] >= '0' && str[l] <= '9')
		{
			num *= 10;
			num += (str[l] - '0');
			if (num > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (num);
}

/**
 * print_err - to print error message
 * @sh_info: an info struct
 * @s: the string containing error type
 * Return: to converted number otherwise, -1 on error
 */
void print_err(siginfo_t *sh_info, char *s)
{
	if (sh_info != NULL)
	{
	// Assuming fname is not a valid member, use the correct member for file name
	prints_string(sh_info->fname);
	prints_string(": ");
	dec_print(sh_info->line_count, STDERR_FILENO);
	prints_string(": ");
	if (sh_info->argv != NULL && sh_info->argv[0] != NULL)
		{
		prints_string(sh_info->argv[0]);
		prints_string(": ");
		}
	}
	prints_string(s);
}

/**
 * prints_string - to print input string
 * @s: the given string
 * Return: Null
 */
void prints_string(char *s)
{
	int l = 0;

	if (!s)
		return;
	while (s[l] != '\0')
	{
		eprintch(s[l]);
		l++;
	}
}

/**
 * dec_print - the function prints decimal number
 * @in: a given input
 * @fd: the file descriptor
 * Return: the number
 */
int dec_print(int in, int fd)
{
	int (*_printch)(char) = _printch;
	int l, c = 0;
	unsigned int _abs_, b;

	if (fd == STDERR_FILENO)
		_printch = eprintch;
	if (in < 0)
	{
		_abs_ = -in;
		_printch('-');
		c++;
	}
	else
		_abs_ = in;
	b = _abs_;
	for (l = 1000000000; l > 1; l /= 10)
	{
		if (_abs_ / l)
		{
			_printch('0' + b / l);
			c++;
		}
		b %= l;
	}
	_printch('0' + b);
	c++;

	return (c);
}

/**
 * rm_comment - to replace the first instance of '#' with '\0'
 * @addr: an address of string to modify
 * Return: null
 */
void rm_comment(char *addr)
{
	int l;

	for (l = 0; addr[l] != '\0'; l++)
		if (addr[l] == '#' && (!l || addr[l - 1] == ' '))
		{
			addr[l] = '\0';
			break;
		}
}
