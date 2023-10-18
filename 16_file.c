#include "main.h"

/**
<<<<<<< HEAD
 * is_chain - to test if current character in buffer is a chain delimeter
 * @info: Parameter struct
 * @buf: character buffer
 * @p: an address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(ino_t *info, char *buf, size_t *p)
=======
 * testchain - to test if current character in buffer is a chain delimeter
 * @info: Parameter struct
 * @buff: a character buffer
 * @p: an address of current position in buff
 * Return: 1 if chain delimeter, 0 otherwise
 */
int testchain(info_t *info, char *buff, size_t *p)
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
{
	size_t a = *p;

	if (buf[a] == '|' && buf[a + 1] == '|')
	{
<<<<<<< HEAD
		buf[a] = 0;
		a++;
=======
		buff[m] = 0;
		m++;
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[a] == '&' && buf[a + 1] == '&')
	{
<<<<<<< HEAD
		buf[a] = 0;
		a++;
=======
		buff[m] = 0;
		m++;
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[a] == ';') /* found end of this command */
	{
<<<<<<< HEAD
		buf[a] = 0; /* replace semicolon with null */
=======
		buff[m] = 0;
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = a;
	return (1);
}

/**
<<<<<<< HEAD
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
=======
 * chainchk - check if we should continue chaining based on last status
 * @info: struct parameter
 * @buff: a character buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @l: the length of buf
 * Return: Void
 */
void chainchk(info_t *info, char *buff, size_t *p, size_t i, size_t l)
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
{
	size_t a = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
<<<<<<< HEAD
		if (info->status)
		{
			buf[i] = 0;
			a = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
=======
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
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
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
<<<<<<< HEAD
 * replace_alias - to replace an aliases in the tokenized string
 * @info: Parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(ino_t *info)
=======
 * vars_rp - replace vars in the tokenized string
 * @info: struct parameter
 * Return: 1 if replaced, 0 otherwise
 */
int vars_rp(info_t *info)
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
{
	int a;
	list_t *node;
	char *p;

<<<<<<< HEAD
	for (a = 0; a < 10; a++)
=======
	while (info->argv[a])
	{
	if (info->argv[a][0] != '$' || !info->argv[a][1])
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
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

<<<<<<< HEAD
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
=======
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
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
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
