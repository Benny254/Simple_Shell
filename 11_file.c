#include "main.h"

/**
 * prtenv - prints current environment
 * @info: structure containing potential arguments
 * Return: Always 0 (Succes)
 */
<<<<<<< HEAD
int prtenv(siginfo_t *sh_info)
=======
int prtenv(info_t *info)
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
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
<<<<<<< HEAD
char *env_var(siginfo_t *sh_info, const char *name)
=======
char *env_var(info_t *info, const char *name)
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
{
	list_t *node = info->env;
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
 * @info: The structure containing potential arguments
 * Return: Always 0 (Success)
 */
<<<<<<< HEAD
int init_env(siginfo_t *sh_info)
=======
int init_env(info_t *info)
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
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
<<<<<<< HEAD
int rem_env(siginfo_t *sh_info)
=======
int rem_env(info_t *info)
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
{
	int a = 1;

	if (info->argc == 1)
	{
	prints_string("Too few arguments.\n");
	return (1);
	}

	while (info->argv[a] != NULL)
	{
<<<<<<< HEAD
	rem_env(sh_info, sh_info->argv[a]);
=======
	rem_venv(info, info->argv[a]);
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
	a++;
	}

	return (0);
}

/**
 * envpop - to populates env linked list
 * @info: structure containing potential arguments
 * Return: Always 0
 */
<<<<<<< HEAD
int envpop(siginfo_t *sh_info)
{
	struct *node = NULL;
=======
int envpop(info_t *info)
{
	list_t *node = NULL;
>>>>>>> 2de96c1583c9be762dc66e70a301f0fb0556db5d
	size_t l = 0;

	while (environ[l] != NULL)
	{
		node_add(&node, environ[l], 0);
	l++;
	}

	info->env = node;
	return (0);
}
