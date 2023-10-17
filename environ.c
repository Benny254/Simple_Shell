#include "main.h"

/**
 * _myenv - To print the current environment
 * @info: The structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - to get the value of an environ variable
 * @info: The structure containing potential arguments. Used to maintain
 * @name: an env var name
 *
 * Return: value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - to initialize a new environment variable,
 *             or modify an existing one
 * @info: The structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - to remove an environment variable
 * @info: The structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int x = 1;

	if (info->argc == 1)
	{
	_eputs("Too few arguments.\n");
	return (1);
	}

	while (info->argv[x] != NULL)
	{
	_unsetenv(info, info->argv[x]);
	x++;
	}

	return (0);
}

/**
 * populate_env_list - to populates env linked list
 * @info: The structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i = 0;

	while (environ[i] != NULL)
	{
		add_node_end(&node, environ[i], 0);
	i++;
	}

	info->env = node;
	return (0);
}
