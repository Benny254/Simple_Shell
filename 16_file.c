#include "main.h"

/**
 * is_chain - to test if current character in buffer is a chain delimeter
 * @info: Parameter struct
 * @buf: character buffer
 * @p: an address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(ino_t *info, char *buf, size_t *p)
{
	size_t a = *p;

	if (buf[a] == '|' && buf[a + 1] == '|')
	{
		buf[a] = 0;
		a++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[a] == '&' && buf[a + 1] == '&')
	{
		buf[a] = 0;
		a++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[a] == ';') /* found end of this command */
	{
		buf[a] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = a;
	return (1);
}

/**
 * check_chain - to check if we should continue chaining based on last status
 * @info: Parameter struct
 * @buf: character buffer
 * @p: an address of current position in buf
 * @i: the starting position in buf
 * @len: the length of buf
 *
 * Return: Void
 */
void check_chain(ino_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t a = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			a = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			a = len;
		}
	}

	*p = a;
}

/**
 * replace_alias - to replace an aliases in the tokenized string
 * @info: Parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(ino_t *info)
{
	int a;
	list_t *node;
	char *p;

	for (a = 0; a < 10; a++)
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

/**
 * replace_vars - to replace vars in the tokenized string
 * @info: Parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(ino_t *info)
{
	int a = 0;
	list_t *node;

	for (a = 0; info->argv[a]; a++)
	{
	if (info->argv[a][0] != '$' || !info->argv[a][1])
		continue;
	if (!_strcmp(info->argv[a], "$?"))
	{
		info->argv[a] = _strdup(convert_number(info->status, 10, 0));
		continue;
	}
	if (!_strcmp(info->argv[a], "$$"))
	{
		info->argv[a] = _strdup(convert_number(getpid(), 10, 0));
		continue;
	}
	node = node_starts_with(info->env, &info->argv[a][1], '=');
	if (node)
	{
		info->argv[a] = _strdup(_strchr(node->str, '=') + 1);
		continue;
	}
	info->argv[a] = _strdup("");
	}
	return (0);
}

/**
 * replace_string - to replace string
 * @old: an address of the old string
 * @new: the new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
