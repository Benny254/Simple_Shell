#include "main.h"

/**
 * _shell - the main shell loop
 * @info: parameter & return info struct
 * @av: argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */
int _shell(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		infoclr(info);
		if (chk_interactive(info))
			print_str("$ ");
		eprintch(BUF_FLUSH);
		r = type_in(info);
		if (r != -1)
		{
			int_info(info, av);
			builtin_ret = builtincmd(info);
			if (builtin_ret == -1)
				cmd_find(info);
		}
		else if (chk_interactive(info))
			printch('\n');
		infofr(info, 0);
	}
	histfile(info);
	infofr(info, 1);
	if (!chk_interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * builtincmd - find a builtin command
 * @info: parameter & return info struct
 * Return: -1 if not found,
 * 0 if executed successfully,
 * 1 if found but not successful,
 * -2 if signals exit()
 */
int builtincmd(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", do_exit},
		{"env", prtenv},
		{"help", help_func},
		{"history", disp_hist},
		{"setenv", init_env},
		{"unsetenv", rem_env},
		{"cd", change_dir},
		{"alias", get_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (comp_str(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * cmd_find - find a command in PATH
 * @info: parameter & return info struct
 * Return: void
 */
void cmd_find(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!delimch(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = chk_cmd(info, env_var(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		run_cmd(info);
	}
	else
	{
		if ((chk_interactive(info) || env_var(info, "PATH=")
			|| info->argv[0][0] == '/') && chk_filetype(info, info->argv[0]))
			run_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_err(info, "not found\n");
		}
	}
}

/**
 * run_cmd - fork an exec thread to run cmd
 * @info: parameter & return info struct
 * Return: void
 */
void run_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, envstr(info)) == -1)
		{
			infofr(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_err(info, "Permission denied\n");
		}
	}
}
