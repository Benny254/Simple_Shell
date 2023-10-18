#include "main.h"

/**
 * testchain - to test if current character in buffer is a chain delimeter
 * @info: Parameter struct
 * @buff: a character buffer
 * @p: an address of current position in buff
 * Return: 1 if chain delimeter, 0 otherwise
 */
int testchain(info_t *info, char *buff, size_t *p)
{
	size_t a = *p;

	if (buf[a] == '|' && buf[a + 1] == '|')
	{
		buff[m] = 0;
		m++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[a] == '&' && buf[a + 1] == '&')
	{
		buff[m] = 0;
		m++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[a] == ';') /* found end of this command */
	{
		buff[m] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = a;
	return (1);
}

/**
 * chainchk - check if we should continue chaining based on last status
 * @info: struct parameter
 * @buff: a character buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @l: the length of buf
 * Return: Void
 */
void chainchk(info_t *info, char *buff, size_t *p, size_t i, size_t l)
{
	size_t m = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buff[i] = 0;
			m = l;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			m = len;
		}
	}

	*p = m;
}

/**
 * vars_rp - replace vars in the tokenized string
 * @info: struct parameter
 * Return: 1 if replaced, 0 otherwise
 */
int vars_rp(info_t *info)
{
	int a;
	list_t *node;
	char *p;

	while (info->argv[a])
	{
	if (info->argv[a][0] != '$' || !info->argv[a][1])
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}
	if (!comp_str(info->argv[a], "$?"))
	{
		new_str(&(info->argv[a])
			dupstr(change_number(info->status, 10, 0)));
		a++;
		continue;
	}
	if (!comp_str(info->argv[a], "$$"))
	{
		new_str(&(info->argv[a]),
			dupstr(change_number(getpid(), 10, 0)));
		a++;
		continue;
	}
	node = node_start(info->env, &info->argv[a][1], '=');
	if (node)
	{
		new_str(&(info->argv[a]),
			dupstr(loc_ch(node->str, '=') + 1));
		a++;
		continue;
	}
	new_str(&info->argv[a], dupstr(""));
	a++;
	}
	return (0);
}
