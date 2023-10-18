#include "main.h"

/**
 * chk_interactive - to check if shell is interactive mode
 * @info: struct
 * Return: 1 if true, 0 otherwise
 */
int chk_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->fdinput <= 2);
}

/**
 * _delim - to check if character is delimeter
 * @ch: the given character
 * @d: Delimeter string
 * Return: 1 if true, 0 otherwise
 */
int _delim(char ch, char *d)
{
	while (*d)
		if (*d++ == ch)
			return (1);
	return (0);
}

/**
 * is_upper - to check  alphabetic character
 * @ch: the given character
 * Return: 1 if true, 0 otherwise
 */
int is_upper(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * convert_string - to convert string to integer
 * @str: the given string
 * Return:the  converted string
 */
int convert_string(char *str)
{
	int l, s = 1, f = 0, n;
	unsigned int out = 0;

	for (l = 0; (str[l] != '\0' && f != 2); l++)
	{
		if (str[l] == '-')
			s *= -1;
		if (str[l] >= '0' && str[l] <= '9')
		{
			f = 1;
			out *= 10;
			out += (str[l] - '0');
		}
		else if (f == 1)
			f = 2;
	}
	if (s == -1)
		n = -out;
	else
		n = out;

	return (n);
}

/**
 * change_number - to convert long integer to character array representing
 * number in a given base
 * @n: the given number
 * @b: the number system in which a given number is represented
 * @f: the flags
 * Return: a string
 */
char *change_number(long int n, int b, int f)
{
	static char *a;
	static char buf[50];
	char s = 0;
	char *p;
	unsigned long number = n;

	if (!(f & CONVERT_UNSIGNED) && n < 0)
	{
		number = -n;
		s = '-';
	}

	a = f & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buf[49];
	*p = '\0';

	do {
		*--p = a[number % b];
		number /= b;
	} while (number != 0);

	if (s)
		*--p = s;
	return (p);
}
