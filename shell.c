#include "main.h"

/**
 * _shell - the main shell loop
 * @sh_info: parameter & return info struct
 * @av: argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */
int _shell(sh_info_t *sh_info, char **av)
{
	ssize_t a = 0;
	int b = 0;

	while (a != -1 && b != -2)
	{
		infoclr(sh_info);
		if (chk_interactive(sh_info))
			print_str("$ ");
		eprintch(BUF_FLUSH);
		a = type_in(sh_info);
		if (a != -1)
		{
			int_info(sh_info, av);
			b = builtincmd(sh_info);
			if (b == -1)
				cmd_find(sh_info);
		}
		else if (chk_interactive(sh_info))
			printch('\n');
		infofr(sh_info, 0);
	}
	histfile(sh_info);
	infofr(sh_info, 1);
	if (!chk_interactive(sh_info) && info->status)
		exit(sh_info->status);
	if (b == -2)
	{
		if (sh_info->err_num == -1)
			exit(sh_info->status);
		exit(sh_info->code_err);
	}
	return (b);
}

/**
 * builtincmd - find a builtin command
 * @sh_info: parameter & return info struct
 * Return: -1 if not found,
 * 0 if executed successfully,
 * 1 if found but not successful,
 * -2 if signals exit()
 */
int builtincmd(sh_info_t *sh_info)
{
	int c, d = -1;
	sh_builtin_table tbl[] = {
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
		if (comp_str(sh_info->argv[0], tbl[c].type) == 0)
		{
			sh_info->line_count++;
			d = tbl[c].func(sh_info);
			break;
		}
	return (d);
}

/**
 * cmd_find - find a command in PATH
 * @sh_info: parameter & return info struct
 * Return: void
 */
void cmd_find(sh_info_t *sh_info)
{
	char *path = NULL;
	int a, y;

	sh_info->path = sh_info->argv[0];
	if (sh_info->linecount_flag == 1)
	{
		sh_info->line_count++;
		sh_info->linecount_flag = 0;
	}
	for (a = 0, y = 0; sh_info->arg[a]; a++)
		if (!_delim(sh_info->arg[a], " \t\n"))
			y++;
	if (!y)
		return;

	path = chk_cmd(sh_info, env_var(sh_info, "PATH="), sh_info->argv[0]);
	if (path)
	{
		sh_info->path = path;
		run_cmd(sh_info);
	}
	else
	{
		if ((chk_interactive(sh_info) || env_var(sh_info, "PATH=")
			|| sh_info->argv[0][0] == '/') && is_cmd(sh_info, sh_info->argv[0]))
			run_cmd(sh_info);
		else if (*(sh_info->arg) != '\n')
		{
			sh_info->status = 127;
			print_err(sh_info, "not found\n");
		}
	}
}

/**
 * run_cmd - fork an exec thread to run cmd
 * @sh_info: parameter & return info struct
 *
 * Return: void
 */
void run_cmd(sh_info_t *sh_info)
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
		if (execve(sh_info->path, sh_info->argv, get_environ(sh_info)) == -1)
		{
			free_info(sh_info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(sh_info->status));
		if (WIFEXITED(sh_info->status))
		{
			info->status = WEXITSTATUS(sh_info->status);
			if (sh_info->status == 126)
				print_err(sh_info, "Permission denied\n");
		}
	}
}
