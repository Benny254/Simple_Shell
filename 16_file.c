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
	size_t m = *p;

	if (buff[m] == '|' && buff[m + 1] == '|')
	{
		buff[m] = 0;
		m++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buff[m] == '&' && buff[m + 1] == '&')
	{
		buff[m] = 0;
		m++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buff[m] == ';')
	{
		buff[m] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = m;
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
	else
	}
	else if (info->cmd_buf_type == CMD_OR)
	{
	if (!info->status)
	{
		buff[i] = 0;
		m = l;
	}
	else
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
	int a = 0;
	list_t *node;

	while (info->argv[a])
	{
	if (info->argv[a][0] != '$' || !info->argv[a][1])
	{
		a++;
		continue;
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
