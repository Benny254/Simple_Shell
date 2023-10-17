#include "main.h"

/**
 * is_chain - to test if current character in buffer is a chain delimeter
 * @info: Parameter struct
 * @buf: a character buffer
 * @p: an address of current position in buf
 *
 * Return: 1 if chain delimeter, then 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
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
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - to check if we should continue chaining based on last status
 * @info: struct parameter
 * @buf: a character buffer
 * @p: an address of current position in buf
 * @i: the starting position in buf
 * @len: the length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
	if (info->status)
	{
		buf[i] = 0;
		j = len;
	}
	else
	}
	else if (info->cmd_buf_type == CMD_OR)
	{
	if (!info->status)
	{
		buf[i] = 0;
		j = len;
	}
	else
	}

	*p = j;
}

/**
 * replace_alias - to replaces an aliases in the tokenized string
 * @info: the struct parameter
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int t = 0;
	list_t *node;
	char *p;

	while (t < 10)
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
	t++;
	}
	return (1);
}

/**
 * replace_vars - to replace vars in the tokenized string
 * @info: the struct parameter
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int t = 0;
	list_t *node;

	while (info->argv[t])
	{
	if (info->argv[t][0] != '$' || !info->argv[t][1])
	{
		t++;
		continue;
	}

	if (!_strcmp(info->argv[t], "$?"))
	{
		replace_string(&(info->argv[t])
			_strdup(convert_number(info->status, 10, 0)));
		t++;
		continue;
	}
	if (!_strcmp(info->argv[t], "$$"))
	{
		replace_string(&(info->argv[t]),
			_strdup(convert_number(getpid(), 10, 0)));
		t++;
		continue;
	}
	node = node_starts_with(info->env, &info->argv[t][1], '=');
	if (node)
	{
		replace_string(&(info->argv[t]),
			_strdup(_strchr(node->str, '=') + 1));
		t++;
		continue;
	}
	replace_string(&info->argv[t], _strdup(""));
	t++;
	}
	return (0);
}
