#include "shell.h"

/**
 * chk_filetype - function checks whether file
 * specified is regular file
 * @sh_info: info struct
 * @filepath: path to file
 * Return: 1 if true, 0 otherwise
 */
int chk_filetype(*sh_info, char *filepath)
{
	struct stat var;

	(void)sh_info;
	if (!filepath || stat(filepath, &var))
		return (0);

	if (var.var_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * chk_cmd - manages PATH environment variable and finds commands
 * executable within specified paths
 * @sh_info: info struct
 * @p_str: PATH string
 * @cmd: cmd to find
 * Return: path of cmd if found, otherwise NULL
 */
char *chk_cmd(info_t *sh_info, char *p_str, char *cmd)
{
	int l = 0, p = 0;
	char *path;

	if (!p_str)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (chk_filetype(sh_info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!p_str[l] || p_str[l] == ':')
		{
			path = cp_char(p_str, p, l);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (chk_filetype(sh_info, path))
				return (path);
			if (!p_str[l])
				break;
			p = l;
		}
		l++;
	}
	return (NULL);
}
