#include "main.h"
/**
 * do_exit - to exit the shell
 * @sh_info: structure containing potential arguments used to maintain
 * constant function prototype
 * Return: to exit with a given exit status
 */
int do_exit(sh_info_t *sh_info)
{
	int checkexit;

	if (sh_info->argv[1])
	{
		checkexit = string_convert(sh_info->argv[1]);
		if (checkexit == -1)
		{
			sh_info->status = 2;
			print_err(info, "Illegal number: ");
			prints_string(sh_info->argv[1]);
			eprintch('\n');
			return (1);
		}
		sh_info->code_err = string_convert(sh_info->argv[1]);
		return (-2);
	}
	sh_info->code_err = -1;
	return (-2);
}
/**
 * change_dir - change the current directory of the process
 * @sh_info: structure containing potential argument used to maintain
 * constant function prototype
 * Return: Always 0
 */
int change_dir(sh_info_t *sh_info)
{
	char *a, *b, buffer[1024];
	int chd;

	a = getcwd(buffer, 1024);
	if (!a)
		prints_str("TODO: >>getcwd failure emsg here<<\n");
	if (!sh_info->argv[1])
	{
		b = env_var(sh_info, "HOME=");
		if (!b)
			chd =
				chdir((dir = env_var(sh_info, "PWD=")) ? dir : "/");
		else
			chd = chdir(dir);
	}
	else if (comp_str(sh_info->argv[1], "-") == 0)
	{
		if (!env_var(sh_info, "OLDPWD="))
		{
			prints_str(a);
			printch('\n');
			return (1);
		}
		print_str(env_var(sh_info, "OLDPWD=")), printch('\n');
		chd =
			chdir((dir = env_var(sh_info, "OLDPWD=")) ? dir : "/");
	}
	else
		chd = chdir(sh_info->argv[1]);
	if (chd == -1)
	{
		print_error(sh_info, "can't cd to ");
		prints_string(sh_info->argv[1]), eprintch('\n');
	}
	else
	{
		init_evar(sh_info, "OLDPWD", env_var(sh_info, "PWD="));
		init_evar(sh_info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * help_func - change the current directory of the process
 * @sh_info: structure containing potential arguments used to maintain
 * constant function prototype
 * Return: Always 0
 */
int help_func(sh_info_t *sh_info)
{
	char **arr_arg;

	arr_arg = sh_info->argv;
	print_str("help call works. Function not yet implemented \n");
	if (0)
		print_str(*arr_arg);
	return (0);
}

/**
 * disp_hist - to display the history list, one command by line preceded
 * with line numbers
 * @sh_info: structure containing potential arguments used to maintain
 * constant function prototype
 * Return: Always 0
 */
int disp_hist(sh_info_t *sh_info)
{
	elem_list(sh_info->node_hist);
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
