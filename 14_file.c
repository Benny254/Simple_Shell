#include "main.h"
#define BUF_FLUSH

/**
 * envstr - return the string array copy of our environ
 * @info: The structure containing potential arguments
 * Return: Always 0
 */
<<<<<<< HEAD
char **envstr(siginfo_t *sh_info)
=======
char **envstr(info_t *info)
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
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
 * @v: string env var property
 * Return: 1 on delete, 0 otherwise
 */
int rem_venv(info_t *info, char *v)
{
	list_t *node = info->env;
	char *p;
	size_t k;

	if (!node || !v)
	return (0);

	for (k = 0; node; k++)
	{
	p = chk_start(node->str, v);
	if (p && *p == '=')
	{
		info->env_changed = node_delete(&(info->env), k);
		k = 0;
		node = info->env;
	}
	else
		{
		node = node->next;
		}
	}
	return (info->env_changed);
}

/**
 * init_evar - to initialize a new environment variable
 * @info: structure containing potential arguments
 * @v: string env var property
 * @value: string env var value
 * Return: Always 0
 */
<<<<<<< HEAD
int init_evar(siginfo_t *sh_info, char *v, char *value)
=======
int init_evar(info_t *info, char *v, char *value)
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
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
	node = info->env;

	for (; node; node = node->next)
	{
	p = chk_start(node->str, v);
	if (p && *p == '=')
	{
		free(node->str);
		node->str = buff;
		info->env_changed = 1;
		free(buff);
		return (0);
	}
		}
		node_add(&(info->env), buff, 0);
		free(buff);
		info->env_changed = 1;
		return (0);
}

/**
 * int_info - initialize sh_info_t struct
 * @info: the struct address
 * @v: argument vector
 */
<<<<<<< HEAD
void int_info(siginfo_t *sh_info, char **v)
=======
void int_info(info_t *info, char **v)
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
{
	int a = 0;

	info->fname = v[0];
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
		a = 0;
		while (info->argv && info->argv[y])
		a++;

		sh_info->argc = a;

		alias_rp(info);
		vars_rp(info);
	}
}

/**
 * infofr - free sh_info_t struct fields
 * @info: struct address
 * @f: true if freeing all fields
 */
<<<<<<< HEAD
void infofr(siginfo_t *sh_info, int f)
=======
void infofr(info_t *info, int f)
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
{
	free_str(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (f)
	{
<<<<<<< HEAD
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
=======
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			node_free(&(info->env));
		if (info->node_hist)
			node_free(&(info->node_hist));
		if (info->alias)
			node_free(&(info->alias));
		free_str(info->environ);
		info->environ = NULL;
		free_p((void **)info->cmd_buf);
		if (info->fdinput > 2)
			close(info->fdinput);
		printch(BUF_FLUSH);
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
	}
}
