#include "main.h"

/**
 * _shell - the main shell loop
 * @info: parameter & return info struct
 * @av: argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */
int _shell(info_t *info, char **av)
{
	ssize_t a = 0;
	int b = 0;

	while (a != -1 && b != -2)
	{
		infoclr(info);
		if (chk_interactive(info))
			print_str("$ ");
		eprintch(BUF_FLUSH);
		a = type_in(info);
		if (a != -1)
		{
			int_info(info, av);
			b = builtincmd(info);
			if (b == -1)
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
	if (b == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->code_err);
	}
	return (b);
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
	int c, d = -1;
	builtin_table tbl[] = {
		{"help", help_func},
		{"history", disp_hist},
		{"setenv", init_env},
		{"exit", do_exit},
		{"env", prtenv},
		{"unsetenv", rem_env},
		{"cd", change_dir},
		{"alias", get_alias},
		{NULL, NULL}
	};

	for (c = 0; tbl[c].type; c++)
		if (comp_str(info->argv[0], tbl[c].type) == 0)
		{
			info->line_count++;
			d = tbl[c].func(info);
			break;
		}
	return (d);
}

/**
 * cmd_find - find a command in PATH
 * @info: parameter & return info struct
 * Return: void
 */
void cmd_find(info_t *info)
{
	char *path = NULL;
	int a, y;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (a = 0, y = 0; info->arg[a]; a++)
		if (!_delim(info->arg[a], " \t\n"))
			y++;
	if (!y)
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
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
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
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
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
