#include "minishell.h"

void	redir_error(t_cmd *cmd)
{
	unlink_temp_files(cmd);
	exit(1);
}

void	run_built_in(t_cmd *cmd, t_list **env)
{
	run_cmd(cmd, env, is_built_in(cmd->simple_cmd), 0);
	exit(error_status);
}

void	close_fd_and_unlink(t_exec *arg, t_cmd *cmd)
{
	close(arg->fds_next[0]);
	close(arg->fds_next[1]);
	unlink_temp_files(cmd);
}