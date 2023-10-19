#include "main.h"

/**
 * alias_reset - to set alias to string
 * @info: Parameter Struct
 * @str: string alias
 * Return: Always 0 on success, 1 on error
 */
int alias_reset(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = loc_ch(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = node_delete(&(info->alias),
		node_get(info->alias, node_start(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * alias_set - set alias to string
 * @info: Parameter Struct
 * @str: string alias
 * Return: 0 on success, 1 on error
 */
int alias_set(info_t *info, char *str)
{
	char *p;

	p = loc_ch(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (alias_reset(info, str));

	alias_reset(info, str);
	return (node_add(&(info->alias), str, 0) == NULL);
}

/**
 * alias_rp - replaces aliases in tokenized string
 * @info: struct parameter
 * Return: 1 if success, 0 otherwise
 */
int alias_rp(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_start(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = loc_ch(node->str, '=');
		if (!p)
			return (0);
		p = dupstr(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * alias_prt - print an alias string
 * @node: alias node
 * Return: 0 on success, 1 on error
 */
int alias_prt(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = loc_ch(node->str, '=');
		for (a = node->str; a <= p; a++)
			printch(*a);
		printch('\'');
		print_str(p + 1);
		print_str("'\n");
		return (0);
	}
	return (1);
}

/**
 * get_alias - mimics alias builtin
 * @info: structure containing potential arguments
 * Return: Always 0(success)
 */
int get_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			alias_prt(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = loc_ch(info->argv[i], '=');
		if (p)
			alias_set(info, info->argv[i]);
		else
			alias_prt(node_starts_with(info->alias, info->argv[i], '='));
	}
	return (0);
}