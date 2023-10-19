#include "main.h"

/**
 * envstr - return the string array copy of our environ
 * @info: The structure containing potential arguments
 * Return: Always 0
 */
char **envstr(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = str_array(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * rem_venv - remove an environment variable
 * @info: the structure containing potential arguments
 * @var: string env var property
 * Return: 1 on delete, 0 otherwise
 */
int rem_venv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = chk_start(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = node_delete(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * init_evar - to initialize a new environment variable
 * @info: structure containing potential arguments
 * @var: string env var property
 * @value: string env var value
 * Return: Always 0
 */
int init_evar(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(len_str(var) + len_str(value) + 2);
	if (!buf)
		return (1);
	cpy_str(buf, var);
	cat_str(buf, "=");
	cat_str(buf, value);
	node = info->env;
	while (node)
	{
		p = chk_start(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	node_add(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

/**
 * int_info - initialize info_t struct
 * @info: the struct address
 * @av: argument vector
 */
void int_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = str_split(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = dupstr(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		alias_rp(info);
		vars_rp(info);
	}
}

/**
 * infofr - free info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void infofr(info_t *info, int all)
{
	free_str(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			node_free(&(info->env));
		if (info->history)
			node_free(&(info->history));
		if (info->alias)
			node_free(&(info->alias));
		free_str(info->environ);
			info->environ = NULL;
		free_p((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		printch(BUF_FLUSH);
	}
}
