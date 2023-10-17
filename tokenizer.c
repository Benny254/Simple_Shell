#include "main.h"

/**
 * **strtow1 - to split a string into words. Repeat delimiters are ignored
 * @str: an input string
 * @d: Delimeter string
 * Return: the pointer to an array of strings, or NULL on failure
 */

char **strtow1(char *str, char *d)
{
	int a, b, l, n, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], d) && (is_delim(str[a + 1], d) || !str[a + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (is_delim(str[a], d))
			a++;
		l = 0;
		while (!is_delim(str[a + l], d) && str[a + l])
			l++;
		s[b] = malloc((l + 1) * sizeof(char));
		if (!s[b])
		{
			for (l = 0; l < b; l++)
				free(s[l]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < l; n++)
			s[b][n] = str[a++];
		s[b][n] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * **strtow3 - to split a string into words
 * @str: an input string
 * @d:  Delimeter
 * Return: the pointer to an array of strings, or NULL on failure
 */
char **strtow3(char *str, char d)
{
	int a, b, l, n, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
		    (str[a] != d && !str[a + 1]) || str[a + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		l = 0;
		while (str[a + l] != d && str[a + l] && str[a + l] != d)
			l++;
		s[b] = malloc((l + 1) * sizeof(char));
		if (!s[b])
		{
			for (l = 0; l < b; l++)
				free(s[l]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < l; n++)
			s[b][n] = str[a++];
		s[b][n] = 0;
	}
	s[b] = NULL;
	return (s);
}
