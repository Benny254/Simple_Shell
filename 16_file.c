#include "main.h"

/**
 * testchain - to test if current character in buffer is a chain delimeter
 * @info: Parameter struct
 * @buf: a character buffer
 * @p: an address of current position in buff
 * Return: 1 if chain delimeter, 0 otherwise
 */
int testchain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * chainchk - check if we should continue chaining based on last status
 * @info: struct parameter
 * @buf: a character buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: the length of buf
 * Return: Void
 */
void chainchk(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * vars_rp - replace vars in the tokenized string
 * @info: struct parameter
 * Return: 1 if replaced, 0 otherwise
 */
int vars_rp(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!comp_str(info->argv[i], "$?"))
		{
			new_str(&(info->argv[i]),
				dupstr(change_number(info->status, 10, 0)));
			continue;
		}
		if (!comp_str(info->argv[i], "$$"))
		{
			new_str(&(info->argv[i]),
				dupstr(change_number(getpid(), 10, 0)));
			continue;
		}
		node = node_start(info->env, &info->argv[i][1], '=');
		if (node)
		{
			new_str(&(info->argv[i]),
				dupstr(loc_ch(node->str, '=') + 1));
			continue;
		}
		new_str(&info->argv[i], dupstr(""));

	}
	return (0);
}
