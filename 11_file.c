#include "main.h"

/**
 * prtenv - prints current environment
 * @info: structure containing potential arguments
 * Return: Always 0 (Succes)
 */
int prtenv(info_t *info)
{
	str_print(info->env);
	return (0);
}

/**
 * env_var - get value of an environ variable
 * @info: structure containing potential arguments
 * @name: env var name
 * Return: value
 */
char *env_var(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = chk_start(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * init_env - to initialize new environment variable
 * or modify existing one
 * @info: The structure containing potential arguments
 * Return: Always 0 (Success)
 */
int init_env(info_t *info)
{
	if (info->argc != 3)
	{
		prints_string("Incorrect number of arguements\n");
		return (1);
	}
	if (init_evar(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * rem_env - remove an environment variable
 * @info: structure containing potential arguments
 * Return: Always 0
 */
int rem_env(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		prints_string("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		rem_venv(info, info->argv[i]);

	return (0);
}

/**
 * envpop - to populates env linked list
 * @info: structure containing potential arguments
 * Return: Always 0
 */
int envpop(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		node_add(&node, environ[i], 0);
	info->env = node;
	return (0);
}
