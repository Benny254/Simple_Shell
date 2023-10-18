#include "main.h"

/**
 * testchain - to test if current character in buffer is a chain delimeter
 * @sh_info: Parameter struct
 * @buff: a character buffer
 * @p: an address of current position in buff
 * Return: 1 if chain delimeter, 0 otherwise
 */
int testchain(sh_info_t *shinfo, char *buff, size_t *p)
{
	size_t m = *p;

	if (buff[m] == '|' && buff[m + 1] == '|')
	{
		buff[m] = 0;
		m++;
		sh_info->cmd_buf_type = CMD_OR;
	}
	else if (buff[m] == '&' && buff[m + 1] == '&')
	{
		buff[m] = 0;
		m++;
		sh_info->cmd_buf_type = CMD_AND;
	}
	else if (buff[m] == ';')
	{
		buff[m] = 0; 
		sh_info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = m;
	return (1);
}

/**
 * chainchk - check if we should continue chaining based on last status
 * @sh_info: struct parameter
 * @buff: a character buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @l: the length of buf
 *
 * Return: Void
 */
void chainchk(sh_info_t *sh_info, char *buff, size_t *p, size_t i, size_t l)
{
	size_t m = *p;

	if (sh_info->cmd_buf_type == CMD_AND)
	{
	if (sh_info->status)
	{
		buff[i] = 0;
		m = l;
	}
	else
	}
	else if (sh_info->cmd_buf_type == CMD_OR)
	{
	if (!sh_info->status)
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
 * @sh_info: struct parameter
 * Return: 1 if replaced, 0 otherwise
 */
int vars_rp(sh_info_t *sh_info)
{
	int a = 0;
	list_t *node;

	while (sh_info->argv[a])
	{
	if (sh_info->argv[a][0] != '$' || !sh_info->argv[a][1])
	{
		a++;
		continue;
	}

	if (!comp_str(sh_info->argv[a], "$?"))
	{
		new_str(&(sh_info->argv[a])
			dupstr(change_number(sh_info->status, 10, 0)));
		a++;
		continue;
	}
	if (!comp_str(sh_info->argv[a], "$$"))
	{
		new_str(&(sh_info->argv[a]),
			dupstr(change_number(getpid(), 10, 0)));
		a++;
		continue;
	}
	node = node_start(sh_info->env, &sh_info->argv[a][1], '=');
	if (node)
	{
		new_str(&(sh_info->argv[a]),
			dupstr(loc_ch(node->str, '=') + 1));
		a++;
		continue;
	}
	new_str(&sh_info->argv[a], dupstr(""));
	a++;
	}
	return (0);
}
