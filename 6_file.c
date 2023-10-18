#include "main.h"

/**
 * alias_string - to set alias to string
 * @info: Parameter Struct
 * @s: string alias
 * Return: Always 0 on success, 1 on error
 */
<<<<<<< HEAD
int alias_string(siginfo_t *sh_info, char *s)
=======
int alias_string(info_t *info, char *s)
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
{
	char *a, b;
	int r;

	a = loc_ch(s, '=');
	if (!a)
		return (1);
	b = *a;
	*a = 0;
	r = node_delete(&(info->alias),
		node_get(info->alias, node_start(info->alias, s, -1)));
	*a = b;
	return (r);
}

/**
 * alias_set - set alias to string
 * @info: Parameter Struct
 * @s: string alias
 * Return: 0 on success, 1 on error
 */
int alias_set(info_t *info, char *s)
{
	char *a;

	a = loc_ch(s, '=');
	if (!a)
		return (1);
	if (!*++a)
<<<<<<< HEAD
		return (alias_reset(siginfo, s));
=======
		return (alias_reset(info, s));
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d

	alias_reset(info, s);
	return (node_add(&(info->alias), s, 0) == NULL);
}

/**
 * alias_rp - replaces aliases in tokenized string
 * @info: struct parameter
 * Return: 1 if success, 0 otherwise
 */
<<<<<<< HEAD
int alias_rp(siginfo_t *sh_info)
=======
int alias_rp(info_t *info)
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
{
	int a = 0;
	list_t *node;
	char *b;

	while (a < 10)
	{
		node = node_start(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		b = loc_ch(node->str, '=');
		if (!b)
			return (0);
		b = dupstr(b + 1);
		if (!b)
			return (0);
		info->argv[0] = b;
		a++;
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
 * @info: structure containing potential arguments
 * Return: Always 0(success)
 */
<<<<<<< HEAD
int get_alias(siginfo_t *sh_info)
=======
int get_alias(info_t *info)
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
{
	int i;
	char *a = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
<<<<<<< HEAD
	for (node = sh_info->sh_alias; node; node = node->next)
	{
		alias_prt(node);
	}
	return (0);
=======
		for (node = info->alias; node; node = node->next)
		{
			alias_prt(node);
		}
		return (0);
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
	}

	for (i = 1; info->argv[i]; i++)
	{
<<<<<<< HEAD
	a = loc_ch(sh_info->argv[i], '=');
	if (a)
		alias_set(sh_info, sh_info->argv[i]);
	else
		alias_prt(node_start(sh_info->sh_alias, sh_info->argv[i], '='));
=======
		a = loc_ch(info->argv[i], '=');
		if (a)
			alias_set(info, info->argv[i]);
		else
			alias_prt(node_start(info->alias, info->argv[i], '='));
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
	}
	return (0);
}
