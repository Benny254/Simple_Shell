#include "main.h"

/**
 * file_hist - to get the history file
 * @info: parameter struct
 * Return: allocated string containg history file
 */
char *file_hist(info_t *info)
{
	char *buf, *dir;

	dir = env_var(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (len_str(dir) + len_str(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	cpy_str(buf, dir);
	cat_str(buf, "/");
	cat_str(buf, HIST_FILE);
	return (buf);
}

/**
 * histfile - create file or appends to an existing file
 * @info:  Parameter struct
 * Return: 1 on success, else -1
 */
int histfile(info_t *info)
{
	ssize_t fd;
	char *filename = file_hist(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		pfd_input(node->str, fd);
		write_ch('\n', fd);
	}
	write_ch(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * histread - read history from file
 * @info: Parameter struct
 * Return: the histcount on success, 0 otherwise
 */
int histread(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = file_hist(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			list_hist(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		list_hist(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		node_delete(&(info->history), 0);
	histnum(info);
	return (info->histcount);
}

/**
 * list_hist - add entry to a history linked list
 * @info: structure containing potential arguments
 * @buf: a buffer
 * @linecount: history linecount
 * Return: Always 0
 */
int list_hist(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	node_add(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * histnum - renumber the history linked list after changes
 * @info: The tructure containing potential arguments
 * Return: new histcount
 */
int histnum(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
