#include "main.h"

/**
 * file_hist - to get the history file
 * @info: parameter struct
 * Return: allocated string containg history file
 */

<<<<<<< HEAD
char *file_hist(siginfo_t *sh_info)
=======
char *file_hist(info_t *info)
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
{
	char *buff, *d;

	d = env_var(info, "HOME=");
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
 * @info:  Parameter struct
 * Return: 1 on success, else -1
 */
<<<<<<< HEAD
int histfile(siginfo_t *sh_info)
=======
int histfile(info_t *info)
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
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
	for (node = info->node_hist; node; node = node->next)
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
<<<<<<< HEAD
int histread(siginfo_t *sh_info)
=======
int histread(info_t *info)
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
{
	int a, b = 0, linecount = 0;
	ssize_t fd, rdlen, f = 0;
	struct stat st;
	char *buff = NULL, *filename = file_hist(info);

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
			list_hist(info, buff + b, linecount++);
			b = a + 1;
		}
	if (b != a)
		list_hist(info, buff + b, linecount++);
	free(buff);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		node_delete(&(info->node_hist), 0);
	histnum(info);
	return (info->histcount);
}

/**
 * list_hist - add entry to a history linked list
 * @info: structure containing potential arguments
 * @buff: a buffer
 * @linecount: history linecount
 * Return: Always 0
 */
<<<<<<< HEAD
int list_hist(siginfo_t *sh_info, char *buff, int linecount)
=======
int list_hist(info_t *info, char *buff, int linecount)
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
{
	list_t *node = NULL;

	if (info->node_hist)
		node = info->node_hist;
	node_add(&node, buff, linecount);

	if (!info->node_hist)
		info->node_hist = node;
	return (0);
}

/**
 * histnum - renumber the history linked list after changes
 * @info: The tructure containing potential arguments
 * Return: new histcount
 */
<<<<<<< HEAD
int histnum(siginfo_t *sh_info)
=======
int histnum(info_t *info)
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
{
	list_t *node = info->node_hist;
	int h = 0;

	while (node)
	{
		node->num = h++;
		node = node->next;
	}
	return (info->histcount = h);
}
