#include "main.h"

/**
 * do_exit - to exit the shell
 * @info: structure containing potential arguments used to maintain
 * constant function prototype
 * Return: to exit with a given exit status
 */
int do_exit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = string_convert(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_err(info, "Illegal number: ");
			prints_string(info->argv[1]);
			eprintch('\n');
			return (1);
		}
		info->err_num = string_convert(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
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
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		print_str("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = env_var(info, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = env_var(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (comp_str(info->argv[1], "-") == 0)
	{
		if (!env_var(info, "OLDPWD="))
		{
			print_str(s);
			printch('\n');
			return (1);
		}
		print_str(env_var(info, "OLDPWD=")), printch('\n');
		chdir_ret =
			chdir((dir = env_var(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_err(info, "can't cd to ");
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
	char **arg_array;

	arg_array = info->argv;
	print_str("help call works. Function not yet implemented \n");
	if (0)
		print_str(*arg_array);
	return (0);
}

/**
 * disp_hist - to display the history list, one command by line preceded
 * with line numbers
 * @info: structure containing potential arguments
 * Return: Always 0
 */
int disp_hist(info_t *info)
{
	elem_list(info->history);
	return (0);
}

/**
 * new_str - replaces a string
 * @old: old string
 * @new: new string
 * Return: 1 if success 0 otherwise
 */
int new_str(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
