#include "main.h"
/**
 * unset_alias - to set alias to string
 * @info: The Parameter Struct
 * @str: a string alias
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - to set alias to string
 * @info: The Parameter Struct
 * @str: A string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *q;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - to print an alias string
 * @node: an alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
	p = _strchr(node->str, '=');
	a = node->str;

	while (a <= p)
	{
		_putchar(*a);
		a++;
	}

	_putchar('\'');
	_puts(p + 1);
	_puts("'\n");
	return (0);
	}
	return (1);
}

/**
 * _myalias - to mimics the alias builtin (man alias)
 * @info: The structure containing potential arguments. Used to maintain
 * constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
	for (node = info->alias; node; node = node->next)
	{
		print_alias(node);
	}
	return (0);
	}

	for (int i = 1; info->argv[i]; i++)
	{
	p = _strchr(info->argv[i], '=');
	if (p)
		set_alias(info, info->argv[i]);
	else
		print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
