#include "main.h"

/**
 * do_exit - to exit the shell
 * @info: structure containing potential arguments used to maintain
 * constant function prototype
 * Return: to exit with a given exit status
 */
int do_exit(info_t *info)
{
	int checkexit;

	if (info->argv[1])
	{
		checkexit = string_convert(info->argv[1]);
		if (checkexit == -1)
		{
			info->status = 2;
			print_err(info, "Illegal number: ");
			prints_string(info->argv[1]);
			eprintch('\n');
			return (1);
		}
		info->code_err = string_convert(info->argv[1]);
		return (-2);
	}
	info->code_err = -1;
	return (-2);
}
/**
 * change_dir - change the current directory of the process
 * @info: structure containing potential argument used to maintain
 * constant function prototype
 * Return: Always 0
 */
int change_dir(info_t *info)
{
	char *a, *b, buffer[1024];
	int chd;

	a = getcwd(buffer, 1024);
	if (!a)
		prints_str("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		b = env_var(info, "HOME=");
		if (!b)
			chd =
				chdir((dir = env_var(info, "PWD=")) ? dir : "/");
		else
			chd = chdir(dir);
	}
	else if (comp_str(info->argv[1], "-") == 0)
	{
		if (!env_var(info, "OLDPWD="))
		{
			prints_str(a);
			printch('\n');
			return (1);
		}
		print_str(env_var(info, "OLDPWD=")), printch('\n');
		chd =
			chdir((dir = env_var(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chd = chdir(info->argv[1]);
	if (chd == -1)
	{
		print_error(info, "can't cd to ");
		prints_string(info->argv[1]), eprintch('\n');
	}
	else
	{
		init_evar(info, "OLDPWD", env_var(info, "PWD="));
		init_evar(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * help_func - change the current directory of the process
 * @info: structure containing potential arguments used to maintain
 * constant function prototype
 * Return: Always 0
 */
int help_func(info_t *info)
{
	char **arr_arg;

	arr_arg = info->argv;
	print_str("help call works. Function not yet implemented \n");
	if (0)
		print_str(*arr_arg);
	return (0);
}

/**
 * disp_hist - to display the history list, one command by line preceded
 * with line numbers
 * @info: structure containing potential arguments used to maintain
 * constant function prototype
 * Return: Always 0
 */
int disp_hist(info_t *info)
{
	elem_list(info->node_hist);
	return (0);
}

/**
 * new_str - replaces a string
 * @a: old string
 * @b: new string
 * Return: 1 if success 0 otherwise
 */
int new_str(char **a, char *b)
{
	free(*a);
	*a = b;
	return (1);
}
