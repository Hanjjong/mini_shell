/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:26:46 by jonhan            #+#    #+#             */
/*   Updated: 2023/08/08 20:59:31 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_exec(t_exec *exec, t_cmd **pipeline, t_list **env)
{
	exec->count = count_pipe(pipeline);
	exec->repeat_fork = 0;
	exec->path = detec_path(env);
}

void	close_fd(t_exec *arg)
{
	close(arg->fds_prev[0]);
	close(arg->fds_prev[1]);
	if (arg->count > 0)
	{
		close(arg->fds_next[1]);
		close(arg->fds_next[0]);
	}
}

void	send_sig(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	evecve_error(char *valid_cmd, char *simple_cmd)
{
	if (valid_cmd)
	{
		if (access(valid_cmd, X_OK) < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(valid_cmd);
			exit(126);
		}
		else
			exit(0);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(simple_cmd, 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
}
