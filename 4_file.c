#include "main.h"

/**
 * chk_filetype - the function checks whether file
 * specified is regular file
 * @info: an info struct
 * @path: the path to file
 * Return: 1 if true, 0 otherwise
 */
int chk_filetype(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * chk_cmd - to manage PATH environment variable and finds commands
 * executable within specified paths
 * @info: an info struct
 * @pathstr: the PATH string
 * @cmd: cmd to find
 * Return: the path of cmd if found, otherwise NULL
 */
char *chk_cmd(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((len_str(cmd) > 2) && chk_start(cmd, "./"))
	{
		if (chk_filetype(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = cp_char(pathstr, curr_pos, i);
			if (!*path)
				cat_str(path, cmd);
			else
			{
				cat_str(path, "/");
				cat_str(path, cmd);
			}
			if (chk_filetype(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * cat_str - concanates two strings
 * @dest: destination buffer
 * @src: source buffer
 * Return: pointer to destination buffer
 */
char *cat_str(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

/**
 * chk_start - check if needle starts with haystack
 * @haystack: string to be searched
 * @needle: substring to find
 * Return: address of next char of haystack, otherwise NULL
 */
char *chk_start(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * len_str - return the length of a string
 * @s: given string
 * Return: length of string
 */
int len_str(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}
