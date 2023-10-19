#include "main.h"

/**
 * string_convert - to convert string representation
 * of integer to integer value
 * @s: the given string
 * Return: the converted number otherwise -1 on error
 */
int string_convert(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_err - to print error message
 * @info: an info struct
 * @estr: the string containing error type
 * Return: to converted number otherwise, -1 on error
 */
void print_err(info_t *info, char *estr)
{
	prints_string(info->fname);
	prints_string(": ");
	dec_print(info->line_count, STDERR_FILENO);
	prints_string(": ");
	prints_string(info->argv[0]);
	prints_string(": ");
	prints_string(estr);
}

/**
 * prints_string - to print input string
 * @str: the given string
 * Return: Null
 */
void prints_string(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		eprintch(str[i]);
		i++;
	}
}

/**
 * dec_print - the function prints decimal number
 * @input: a given input
 * @fd: the file descriptor
 * Return: the number
 */
int dec_print(int input, int fd)
{
	int (*_printch)(char) = printch;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		_printch = eprintch;
	if (input < 0)
	{
		_abs_ = -input;
		_printch('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			_printch('0' + current / i);
			count++;
		}
		current %= i;
	}
	_printch('0' + current);
	count++;

	return (count);
}

/**
 * rm_comment - to replace the first instance of '#' with '\0'
 * @buf: an address of string to modify
 * Return: null
 */
void rm_comment(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
