#include "shell.h"

/**
 * string_convert - convert string representation of integer to integer value
 * @str: given string
 * Return: converted number otherwise -1 on error
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
 * print_err - prints error message
 * @sh_info: info struct
 * @s: string containing error type
 * Return: converted number otherwise, -1 on error
 */
void print_err(info_t *sh_info, char *s)
{
	prints_string(sh_info->fname);
	prints_string(": ");
	dec_print(sh_info->line_count, STDERR_FILENO);
	prints_string(": ");
	prints_string(sh_info->argv[0]);
	prints_string(": ");
	prints_string(s);
}

/**
 * prints_string - prints input string
 * @s: given string
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
 * dec_print - function prints decimal number
 * @in: given input
 * @fd: file descriptor
 * Return: number
 */
int dec_print(int in, int fd)
{
	int (*__putchar)(char) = _putchar;
	int l, c = 0;
	unsigned int _abs_, b;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (in < 0)
	{
		_abs_ = -in;
		__putchar('-');
		c++;
	}
	else
		_abs_ = in;
	b = _abs_;
	for (l = 1000000000; l > 1; l /= 10)
	{
		if (_abs_ / l)
		{
			__putchar('0' + b / l);
			c++;
		}
		b %= l;
	}
	__putchar('0' + b);
	c++;

	return (c);
}

/**
 * rm_comment - replaces first instance of '#' with '\0'
 * @addr: address of string to modify
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
