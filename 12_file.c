#include "main.h"

/**
 * buf_input - to buffers chained commands
 * @info: parameter struct
 * @buf: an address of buffer
 * @len: an address of len var
 * Return: the bytes read
 */
ssize_t buf_input(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, handlec);
#if USE_GETLINE
		r = nextline(buf, &len_p, stdin);
#else
		r = nextline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			rm_comment(*buf);
			list_hist(info, *buf, info->histcount++);
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * type_in - get a line minus the newline
 * @info: the parameter struct
 * Return: the bytes read
 */
ssize_t type_in(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	printch(BUF_FLUSH);
	r = buf_input(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		chainchk(info, buf, &j, i, len);
		while (j < len)
		{
			if (testchain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (len_str(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * bufread - read a buffer
 * @info: the parameter struct
 * @buf: a buffer
 * @i: the size
 * Return: r
 */
ssize_t bufread(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * nextline - get the next line of an input from STDIN
 * @info: parameter struct
 * @ptr: an address of a pointer to buffer
 * @length: the size of preallocated ptr buffer
 * Return: s
 */
int nextline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = bufread(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = loc_ch(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = allocmem(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		concat_str(new_p, buf + i, k - i);
	else
		cppy_str(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * handlec - the block ctrl-C
 * @sig_num: signal number
 * Return: the void
 */
void handlec(__attribute__((unused))int sig_num)
{
	print_str("\n");
	print_str("$ ");
	printch(BUF_FLUSH);
}
