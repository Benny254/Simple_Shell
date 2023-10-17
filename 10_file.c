#include "main.h"

/**
 * **string_split - split a string into words
 * @str: input string
 * @d: delimeter
 * Return: the pointer to an array of strings, or NULL on failure
 */
char **string_split(char *str, char d)
{
	int a, b, l, n, numw = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
				(str[a] != d && !str[a + 1]) || str[a + 1] == d)
			numw++;
	if (numw == 0)
		return (NULL);
	s = malloc((1 + numw) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numw; b++)
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

/**
 * **str_split - split a string into words & repeat delimiters are ignored
 * @str: an input string
 * @d: delimeter string
 * Return: the pointer to an array of strings or NULL otherwise
 */
char **str_split(char *str, char *d)
{
	int a, b, l, n, numw = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!delimch(str[a], d) && (delimch(str[a + 1], d) || !str[a + 1]))
			numw++;

	if (numw == 0)
		return (NULL);
	s = malloc((1 + numw) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numw; b++)
	{
		while (delimch(str[a], d))
			a++;
		l = 0;
		while (!delimch(str[a + l], d) && str[a + l])
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
 * allocmem- reallocate a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @a: the byte size of previous block
 * @b: to byte size of new block
 * Return: the pointer to da ol'block nameen.
 */
void *allocmem(void *ptr, unsigned int a, unsigned int b)
{
	char *p;

	if (!ptr)
		return (malloc(b));
	if (!b)
		return (free(ptr), NULL);
	if (b == a)
		return (ptr);

	p = malloc(b);
	if (!p)
		return (NULL);

	a = a < b ? a : b;
	while (a--)
		p[a] = ((char *)ptr)[a];
	free(ptr);
	return (p);
}

/**
 **bytemem - fill memory with constant byte
 *@s: a pointer to the memory area
 *@b: a byte to fill *s with
 *@n: an amount of bytes to be filled
 *Return: (s)
 */
char *bytemem(char *s, char b, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
		s[a] = b;
	return (s);
}

/**
 * free_str - free a string of strings
 * @k: string to free
 * Return: void
 */
void free_str(char **k)
{
	char **a = k;

	if (!k)
		return;
	while (*k)
		free(*k++);
	free(a);
}
