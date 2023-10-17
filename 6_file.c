include "main.h"

/**
 * alias_string - to set alias to string
 * @sh_info: Parameter Struct
 * @s: string alias
 * Return: Always 0 on success, 1 on error
 */
int alias_string(sh_info_t *sh_info, char *s)
{
	char *a, b;
	int r;

	a = loc_ch(s, '=');
	if (!a)
		return (1);
	b = *a;
	*a = 0;
	r = node_delete(&(sh_info->sh_alias),
		node_get(sh_info->sh_alias, node_start(sh_info->sh_alias, s, -1)));
	*a = b;
	return (r);
}

/**
 * alias_set - set alias to string
 * @sh_info: Parameter Struct
 * @s: string alias
 * Return: 0 on success, 1 on error
 */
int alias_set(sh_info_t *sh_info, char *s)
{
	char *a;

	a = loc_ch(s, '=');
	if (!a)
		return (1);
	if (!*++a)
		return (alias_reset(sh_info, s));

	alias_reset(sh_info, s);
	return (node_add(&(sh_info->sh_alias), s, 0) == NULL);
}

/**
 * alias_rp - replaces aliases in tokenized string
 * @sh_info: struct parameter
 * Return: 1 if success, 0 otherwise
 */
int alias_rp(sh_info_t *sh_info)
{
	int a = 0;
	sh_list_t *node;
	char *b;

	while (a < 10)
	{
		node = node_start(sh_info->sh_alias, sh_info->argv[0], '=');
		if (!node)
			return (0);
		free(sh_info->argv[0]);
		b = loc_ch(node->str, '=');
		if (!b)
			return (0);
		b = dupstr(b + 1);
		if (!b)
			return (0);
		sh_info->argv[0] = b;
		a++;
	}
	return (1);
}

/**
 * alias_prt - print an alias string
 * @node: alias node
 * Return: 0 on success, 1 on error
 */
int alias_prt(sh_list_t *node)
{
	char *a = NULL, *b = NULL;

	if (node)
	{
		a = loc_ch(node->str, '=');
		b = node->str;

		while (b <= a)
		{
			printch(*b);
			b++;
		}

		printch('\'');
		print_str(a + 1);
		print_str("'\n");
		return (0);
	}
	return (1);
}

/**
 * get_alias - mimics alias builtin
 * @sh_info: structure containing potential arguments
 * Return: Always 0(success)
 */
int get_alias(sh_info_t *sh_info)
{
	int i;
	char *a = NULL;
	list_t *node = NULL;

	if (sh_info->argc == 1)
	{
		for (node = sh_info->sh_alias; node; node = node->next)
		{
			alias_prt(node);
		}
		return (0);
	}

	for (i = 1; sh_info->argv[i]; i++)
	{
		a = loc_ch(sh_info->argv[i], '=');
		if (a)
			alias_set(sh_info, sh_info->argv[i]);
		else
			alias_prt(node_start(sh_info->sh_alias, sh_info->argv[i], '='));
	}
	return (0);
}
