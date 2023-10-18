#include "main.h"

/**
 * buf_input - to buffers chained commands
 * @info: parameter struct
 * @buff: an address of buffer
 * @len: an address of len var
 * Return: the bytes read
 */
ssize_t buf_input(info_t *info, char **buff, size_t *len)
{
	ssize_t a = 0;
	size_t p = 0;

	if (!*len)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		a = getline(buff, &p, stdin);
#else
		a = _getline(info, buff, &p);
#endif
		if (a > 0)
		{
			if ((*buff)[a - 1] == '\n')
			{
				(*buff)[a - 1] = '\0';
				t--;
			}
			info->linecount_flag = 1;
			remove_comments(*buff);
			list_hist(info, *buff, info->histcount++);
			{
				*len = a;
				info->cmd_buf = buff;
			}
		}
	}
	return (a);
}

/**
 * type_in - get a line minus the newline
 * @info: the parameter struct
 * Return: the bytes read
 */
ssize_t type_in(info_t *info)
{
	static char *buff;
	static size_t a, b, l;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	printch(BUF_FLUSH);
	r = buf_input(info, &buff, &l);
	if (r == -1) /* EOF */
	return (-1);
	if (l)
	{
	b = a;
	p = buff + a;

	chainchk(info, buff, &b, a, l);
	for (; b < l; b++)
	{
		if (testchain(info, buff, &b))
		break;
	}

	a = b + 1;
	if (a >= l)
	{
		a = l = 0;
		info->cmd_buf_type = CMD_NORM;
	}

	*buf_p = p;
	return (len_str(p));
	}

	*buf_p = buff;
	return (r);
}

/**
 * bufread - read a buffer
 * @info: the parameter struct
 * @buff: a buffer
 * @s: the size
 * Return: l
 */
ssize_t bufread(info_t *info, char *buff, size_t *s)
{
	ssize_t l = 0;

	if (*s)
		return (0);
	j = read(info->readfd, buff, READ_BUF_SIZE);
	if (l >= 0)
		*s = l;
	return (l);
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
	static char buff[READ_BUF_SIZE];
	static size_t a, len;
	size_t l;
	ssize_t r = 0, s = 0;
	char *p = NULL, *p2 = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (a == len)
		a = len = 0;

	r = read_buf(info, buff, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = loc_ch(buff + a, '\n');
	l = c ? 1 + (unsigned int)(c - buff) : len;
	p2 = _realloc(p, s, s ? s + l : l + 1);
	if (!p2)
		return (p ? free(p), -1 : -1);

	if (s)
		concat_str(p2, buff + a, l - a);
	else
		cppy_str(p2, buff + a, l - a + 1);

	s += l - a;
	a = l;
	p = p2;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * handlec - the block ctrl-C
 * @s: signal number
 * Return: the void
 */
void handlec(__attribute__((unused))int s)
{
	print_str("\n");
	print_str("$ ");
	printch(BUF_FLUSH);
}
