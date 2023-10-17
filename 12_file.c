#include "main.h"

/**
 * buf_input - to buffers chained commands
 * @sh_info: parameter struct
 * @buff: an address of buffer
 * @len: an address of len var
 * Return: the bytes read
 */
ssize_t buf_input(sh_info_t *sh_info, char **buff, size_t *len)
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
		a = _getline(sh_info, buff, &p);
#endif
		if (a > 0)
		{
			if ((*buff)[a - 1] == '\n')
			{
				(*buff)[a - 1] = '\0';
				t--;
			}
			sh_info->linecount_flag = 1;
			remove_comments(*buff);
			list_hist(sh_info, *buff, sh_info->histcount++);
			{
				*len = a;
				sh_info->cmd_buf = buff;
			}
		}
	}
	return (a);
}

/**
 * type_in - get a line minus the newline
 * @sh_info: the parameter struct
 * Return: the bytes read
 */
ssize_t type_in(sh_info_t *sh_info)
{
	static char *buff;
	static size_t a, b, l;
	ssize_t r = 0;
	char **buf_p = &(sh_info->arg), *p;

	printch(BUF_FLUSH);
	r = buf_input(sh_info, &buff, &l);
	if (r == -1) /* EOF */
	return (-1);
	if (l)
	{
	b = a;
	p = buff + a;

	chainchk(sh_info, buff, &b, a, l);
	for (; b < l; b++)
	{
		if (testchain(sh_info, buff, &b))
		break;
	}

	a = b + 1;
	if (a >= l)
	{
		a = l = 0;
		sh_info->cmd_buf_type = CMD_NORM;
	}

	*buf_p = p;
	return (len_str(p));
	}

	*buf_p = buff;
	return (r);
}

/**
 * bufread - read a buffer
 * @sh_info: the parameter struct
 * @buff: a buffer
 * @s: the size
 * Return: l
 */
ssize_t bufread(sh_info_t *sh_info, char *buff, size_t *s)
{
	ssize_t l = 0;

	if (*s)
		return (0);
	j = read(sh_info->readfd, buff, READ_BUF_SIZE);
	if (l >= 0)
		*s = l;
	return (l);
}

/**
 * nextline - get the next line of an input from STDIN
 * @sh_info: parameter struct
 * @ptr: an address of a pointer to buffer
 * @length: the size of preallocated ptr buffer
 * Return: s
 */
int nextline(sh_info_t *sh_info, char **ptr, size_t *length)
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

	r = read_buf(sh_info, buff, &len);
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
