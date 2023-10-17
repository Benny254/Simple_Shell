#include "main.h"

/**
 * file_hist - to get the history file
 * @sh_info: parameter struct
 * Return: allocated string containg history file
 */

char *file_hist(sh_info_t *sh_info)
{
	char *buff, *d;

	d = env_var(sh_info, "HOME=");
	if (!d)
		return (NULL);
	buff = malloc(sizeof(char) * (len_str(d) + len_str(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	cpy_str(buff, d);
	cat_str(buff, "/");
	cat_str(buff, HIST_FILE);
	return (buff);
}

/**
 * histfile - create file or appends to an existing file
 * @sh_info:  Parameter struct
 * Return: 1 on success, else -1
 */
int histfile(sh_info_t *sh_info)
{
	ssize_t fd;
	char *filename = file_hist(sh_info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = sh_info->node_hist; node; node = node->next)
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
 * @sh_info: Parameter struct
 * Return: the histcount on success, 0 otherwise
 */
int histread(sh_info_t *sh_info)
{
	int a, b = 0, linecount = 0;
	ssize_t fd, rdlen, f = 0;
	struct stat st;
	char *buff = NULL, *filename = file_hist(sh_info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		f = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (f + 1));
	if (!buff)
		return (0);
	rdlen = read(fd, buff, f);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (a = 0; a < f; a++)
		if (buff[i] == '\n')
		{
			buff[a] = 0;
			list_hist(sh_info, buff + b, linecount++);
			b = a + 1;
		}
	if (b != a)
		list_hist(info, buff + b, linecount++);
	free(buff);
	sh_info->histcount = linecount;
	while (sh_info->histcount-- >= HIST_MAX)
		node_delete(&(sh_info->node_hist), 0);
	histnum(sh_info);
	return (sh_info->histcount);
}

/**
 * list_hist - add entry to a history linked list
 * @sh_info: structure containing potential arguments
 * @buff: a buffer
 * @linecount: history linecount
 * Return: Always 0
 */
int list_hist(sh_info_t *sh_info, char *buff, int linecount)
{
	list_t *node = NULL;

	if (sh_info->node_hist)
		node = info->node_hist;
	node_add(&node, buff, linecount);

	if (!sh_info->node_hist)
		sh_info->node_hist = node;
	return (0);
}

/**
 * histnum - renumber the history linked list after changes
 * @sh_info: The tructure containing potential arguments
 * Return: new histcount
 */
int histnum(sh_info_t *sh_info)
{
	list_t *node = sh_info->node_hist;
	int h = 0;

	while (node)
	{
		node->num = h++;
		node = node->next;
	}
	return (sh_info->histcount = h);
}
