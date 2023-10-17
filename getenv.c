#include "main.h"

/**
 * get_environ - to return the string array copy of our environ
 * @info: The structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - to remove an environment variable
 * @info: the structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: a string env var property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	char *p;
	size_t j;

	if (!node || !var)
	return (0);

	for (j = 0; node; j++)
	{
	p = starts_with(node->str, var);
	if (p && *p == '=')
	{
		info->env_changed = delete_node_at_index(&(info->env), j);
		j = 0;
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
 * _setenv - to initialize a new environment variable,
 *             or modify an existing one
 * @info: The structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: a string env var property
 * @value: a string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
	return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
	return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;

	for (; node; node = node->next)
	{
	p = starts_with(node->str, var);
	if (p && *p == '=')
	{
		free(node->str);
		node->str = buf;
		info->env_changed = 1;
		free(buf);
		return (0);
	}
		}
		add_node_end(&(info->env), buf, 0);
		free(buf);
		info->env_changed = 1;
		return (0);
}
