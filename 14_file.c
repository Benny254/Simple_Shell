#include "main.h"
#define BUF_FLUSH

/**
 * envstr - return the string array copy of our environ
 * @sh_info: The structure containing potential arguments
 * Return: Always 0
 */
char **envstr(siginfo_t *sh_info)
{
	if (!sh_info->environ || sh_info->env_changed)
	{
		sh_info->environ = str_array(sh_info->env);
		sh_info->env_changed = 0;
	}

	return (sh_info->environ);
}

/**
 * rem_venv - remove an environment variable
 * @sh_info: the structure containing potential arguments
 * @v: string env var property
 * Return: 1 on delete, 0 otherwise
 */
int rem_venv(sh_info_t *sh_info, char *v)
{
	list_t *node = sh_info->env;
	char *p;
	size_t k;

	if (!node || !v)
	return (0);

	for (k = 0; node; k++)
	{
	p = chk_start(node->str, v);
	if (p && *p == '=')
	{
		sh_info->env_changed = node_delete(&(sh_info->env), k);
		k = 0;
		node = sh_info->env;
	}
	else
		{
		node = node->next;
		}
	}
	return (sh_info->env_changed);
}

/**
 * init_evar - to initialize a new environment variable
 * @sh_info: structure containing potential arguments
 * @v: string env var property
 * @value: string env var value
 * Return: Always 0
 */
int init_evar(siginfo_t *sh_info, char *v, char *value)
{
	char *buff = NULL;
	list_t *node;
	char *p;

	if (!v || !value)
	return (0);

	buff = malloc(len_str(v) + len_str(value) + 2);
	if (!buff)
	return (1);
	cpy_str(buff, v);
	cat_str(buff, "=");
	cat_str(buff, value);
	node = sh_info->env;

	for (; node; node = node->next)
	{
	p = chk_start(node->str, v);
	if (p && *p == '=')
	{
		free(node->str);
		node->str = buff;
		sh_info->env_changed = 1;
		free(buff);
		return (0);
	}
		}
		node_add(&(sh_info->env), buff, 0);
		free(buff);
		sh_info->env_changed = 1;
		return (0);
}

/**
 * int_info - initialize sh_info_t struct
 * @sh_info: the struct address
 * @v: argument vector
 */
void int_info(siginfo_t *sh_info, char **v)
{
	int a = 0;

	sh_info->fname = v[0];
	if (sh_info->arg)
	{
	sh_info->argv = str_split(sh_info->arg, " \t");
	if (!sh_info->argv)
	{
		sh_info->argv = malloc(sizeof(char *) * 2);
	if (sh_info->argv)
		{
		sh_info->argv[0] = dupstr(sh_info->arg);
		sh_info->argv[1] = NULL;
		}
	}
		a = 0;
		while (sh_info->argv && sh_info->argv[y])
		a++;

		sh_info->argc = a;

		alias_rp(sh_info);
		vars_rp(sh_info);
	}
}

/**
 * infofr - free sh_info_t struct fields
 * @sh_info: struct address
 * @f: true if freeing all fields
 */
void infofr(siginfo_t *sh_info, int f)
{
	free_str(sh_info->argv);
	sh_info->argv = NULL;
	sh_info->path = NULL;
	if (f)
	{
		if (!sh_info->cmd_buf)
			free(sh_info->arg);
		if (sh_info->env)
			node_free(&(sh_info->env));
		if (sh_info->node_hist)
			node_free(&(infofr->node_hist));
		if (sh_info->sh_alias)
			node_free(&(sh_info->sh_alias));
		free_str(sh_info->environ);
			sh_info->environ = NULL;
		free_p((void **)sh_info->cmd_buf);
		if (sh_info->fdinput > 2)
			close(sh_info->fdinput);
		eprintch(BUF_FLUSH);
	}
}
