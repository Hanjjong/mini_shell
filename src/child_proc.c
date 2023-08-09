/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:07:33 by jonhan            #+#    #+#             */
/*   Updated: 2023/08/09 19:07:09 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	first_child(t_exec arg, t_cmd *cmd, t_list **env)
{
	char	*valid_cmd;
	char	**envp;

	envp = make_envp(env);
	if (init_redir(cmd) == 1)
		redir_error(cmd);
	dup2(cmd->io_fd[0], STDIN_FILENO);
	if (cmd->io_fd[1] != 1)
		dup2(cmd->io_fd[1], STDOUT_FILENO);
	else if (arg.count > 1)
		dup2(arg.fds_next[1], STDOUT_FILENO);
	if (cmd->io_fd[1] != 1)
		close(cmd->io_fd[1]);
	if (cmd->io_fd[0] != 0)
		close(cmd->io_fd[0]);
	close_fd_and_unlink(&arg, cmd);
	if (is_built_in(cmd->simple_cmd) > -1)
		run_built_in(cmd, env);
	if (cmd->simple_cmd[0] == NULL)
		exit(error_status);
	valid_cmd = valid(arg.path, cmd->simple_cmd[0]);
	if (!valid_cmd && !access(cmd->simple_cmd[0], F_OK))
		valid_cmd = cmd->simple_cmd[0];
	if (execve(valid_cmd, cmd->simple_cmd, envp) < 0)
		evecve_error(valid_cmd, cmd->simple_cmd[0]);
}


void	middle_child(t_exec arg, t_cmd *cmd, t_list **env)
{
	char	*valid_cmd;
	char	**envp;

	envp = make_envp(env);
	close(arg.fds_next[0]);
	close(arg.fds_prev[1]);
	if (init_redir(cmd) == 1)
		redir_error(cmd);
	if (cmd->io_fd[1] != 1)
		dup2(cmd->io_fd[1], STDOUT_FILENO);
	else
		dup2(arg.fds_next[1], STDOUT_FILENO);
	if (cmd->io_fd[0] != 0)
		dup2(cmd->io_fd[0], STDIN_FILENO);
	else
		dup2(arg.fds_prev[0], STDIN_FILENO);
	if (cmd->io_fd[0] != 0)
		close(cmd->io_fd[0]);
	else
		close(arg.fds_prev[0]);
	if (cmd->io_fd[1] != 1)
		close(cmd->io_fd[1]);
	else
		close(arg.fds_next[1]);
	unlink_temp_files(cmd);
	if (is_built_in(cmd->simple_cmd) > -1)
		run_built_in(cmd, env);
	if (cmd->simple_cmd[0] == NULL)
		exit(error_status);
	valid_cmd = valid(arg.path, cmd->simple_cmd[0]);
	if (!valid_cmd && !access(cmd->simple_cmd[0], F_OK))
		valid_cmd = cmd->simple_cmd[0];
	if (execve(valid_cmd, cmd->simple_cmd, envp) < 0)
		evecve_error(valid_cmd, cmd->simple_cmd[0]);
}

void	last_child(t_exec arg, t_cmd *cmd, t_list **env)
{
	char	*valid_cmd;
	char	**envp;

	envp = make_envp(env);
	if (init_redir(cmd) == 1)
		redir_error(cmd);
	if (cmd->io_fd[1] != 1)
		dup2(cmd->io_fd[1], STDOUT_FILENO);
	if (cmd->io_fd[0] != 0)
		dup2(cmd->io_fd[0], STDIN_FILENO);
	else
		dup2(arg.fds_prev[0], STDIN_FILENO);
	if (cmd->io_fd[0] != 0)
		close(cmd->io_fd[0]);
	if (cmd->io_fd[1] != 1)
		close(cmd->io_fd[1]);
	close(arg.fds_prev[1]);
	close(arg.fds_prev[0]);
	close_fd_and_unlink(&arg, cmd);
	if (is_built_in(cmd->simple_cmd) > -1)
		run_built_in(cmd, env);
	if (cmd->simple_cmd[0] == NULL)
		exit(error_status);
	valid_cmd = valid(arg.path, cmd->simple_cmd[0]);
	if (!valid_cmd && !access(cmd->simple_cmd[0], F_OK))
		valid_cmd = cmd->simple_cmd[0];
	if (execve(valid_cmd, cmd->simple_cmd, envp) < 0)
		evecve_error(valid_cmd, cmd->simple_cmd[0]);
}

void	wait_child(pid_t pid, int count)
{
	int	fork_count;
	int	status;

	fork_count = 0;
	while (pid != 0 && fork_count < count)
	{
		if (waitpid(-1, &status, 0) > 0)
		{
			if (WIFEXITED(status))
				error_status = WEXITSTATUS(status);
			else if (WTERMSIG(status) == 2)
				error_status = 130;
			else if (WTERMSIG(status) == 3)
			{
				error_status = 131;
				printf("QUIT: 3\n");
			}
		}
		else
			return ;
		fork_count++;
	}
	return ;
}


