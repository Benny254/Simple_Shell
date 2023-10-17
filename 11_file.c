#include "main.h"

/**
 * prtenv - prints current environment
 * @sh_info: structure containing potential arguments
 * Return: Always 0 (Succes)
 */
int _myenv(sh_info_t *sh_info)
{
	str_print(sh_info->env);
	return (0);
}

/**
 * env_var - get value of an environ variable
 * @sh_info: structure containing potential arguments
 * @name: env var name
 * Return: value
 */
char *env_var(sh_info_t *sh_info, const char *name)
{
	list_t *node = sh_info->env;
	char *a;

	while (node)
	{
		a = chk_start(node->str, name);
		if (a && *a)
			return (a);
		node = node->next;
	}
	return (NULL);
}

/**
 * init_env - to initialize new environment variable
 * or modify existing one
 * @sh_info: The structure containing potential arguments
 * Return: Always 0 (Success)
 */
int init_env(sh_info_t *sh_info)
{
	if (sh_info->argc != 3)
	{
		prints_string("Incorrect number of arguements\n");
		return (1);
	}
	if (init_evar(sh_info, sh_info->argv[1], sh_info->argv[2]))
		return (0);
	return (1);
}

/**
 * rem_env - remove an environment variable
 * @sh_info: structure containing potential arguments
 * Return: Always 0
 */
int rem_env(sh_info_t *sh_info)
{
	int a = 1;

	if (sh_info->argc == 1)
	{
	prints_string("Too few arguments.\n");
	return (1);
	}

	while (sh_info->argv[a] != NULL)
	{
	rem_venv(sh_info, sh_info->argv[a]);
	a++;
	}

	return (0);
}

/**
 * envpop - to populates env linked list
 * @sh_info: structure containing potential arguments
 * Return: Always 0
 */
int envpop(sh_info_t *sh_info)
{
	sh_list_t *node = NULL;
	size_t l = 0;

	while (environ[l] != NULL)
	{
		node_add(&node, environ[l], 0);
	l++;
	}

	sh_info->env = node;
	return (0);
}
