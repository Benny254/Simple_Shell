#include "shell.h"

/**
 * chk_interactive - checks if shell is interactive mode
 * @sh_info: struct
 * Return: 1 if true, 0 otherwise
 */
int chk_interactive(info_t *sh_info)
{
	return (isatty(STDIN_FILENO) && sh_info->readfd <= 2);
}

/**
 * _delim - checks if character is delimeter
 * @ch: given character
 * @d: delimeter string
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
 * is_upper - checks  alphabetic character
 * @ch: given character
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
 * convert_string - convert string to integer
 * @str: given string
 * Return: converted string
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
 * change_number - converts long integer to character array representing
 * number in a given base
 * @n: given number
 * @b: number system in which a given number is represented
 * @f: flags
 * Return: string
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
