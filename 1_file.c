#include "main.h"

/**
 * chk_interactive - to check if shell is interactive mode
 * @info: struct
 * Return: 1 if interactive mode, 0 if not
 */
int chk_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * delimch - to check if character is delimeter
 * @c: the given character
 * @delim: Delimeter string
 * Return: 1 if true, 0 otherwise
 */
int delimch(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * is_upper - to check  alphabetic character
 * @c: the given character
 * Return: 1 if true, 0 otherwise
 */
int is_upper(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * convert_string - to convert string to integer
 * @s: the given string
 * Return: converted string
 */
int convert_string(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; (s[i] != '\0' && flag != 2); i++)
	{
		if (s[i] == '-')
			sign *= -1;
		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

/**
 * change_number - to convert long integer to character array representing
 * number in a given base
 * @num: the given number
 * @base: the number system in which a given number is represented
 * @flags: the flags
 * Return: ptr
 */
char *change_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}
