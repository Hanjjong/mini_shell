#include "minishell.h"

int	is_built_in(char **simple_cmd)
{
	char	*cmd;

	cmd = simple_cmd[0];
	if (!ft_strcmp(cmd, "exit"))
		return (0);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (2);
	else if (!ft_strcmp(cmd, "export"))
		return (3);
	else if (!ft_strcmp(cmd, "unset"))
		return (4);
	else if (!ft_strcmp(cmd, "env"))
		return (5);
	else if (!ft_strcmp(cmd, "echo"))
		return (6);
	return (-1);
}

void	run_cmd(t_cmd *cmd, t_list **environ)
{
	void	(*f[7])(char **, t_list **, int);
	int		idx;

	f[0] = ft_exit;
	f[1] = ft_pwd;
	f[2] = ft_cd;
	f[3] = ft_export;
	f[4] = ft_unset;
	f[5] = ft_env;
	f[6] = ft_echo;
	idx = is_built_in(cmd->simple_cmd);
	if (idx > -1)
		f[idx](cmd->simple_cmd, environ, 1);
	else
		return ; //execve
}