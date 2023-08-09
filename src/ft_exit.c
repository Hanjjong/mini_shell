/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:48:03 by jonhan            #+#    #+#             */
/*   Updated: 2023/08/09 13:48:03 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **simple_cmd, t_list **environ, int fd)
{
	unsigned char	exit_status;

	(void)fd;
	if (!environ)
		return ;
	exit_status = 0;
	if (simple_cmd[1] && ft_atouc(simple_cmd[1], &exit_status) == 0)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(simple_cmd[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		error_status = 255;
		exit(255);
	}
	else if (simple_cmd[1] && simple_cmd[2])
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(simple_cmd[1], 2);
		ft_putendl_fd(": too many arguments", 2);
		error_status = 255;
		exit(255);
	}
	ft_putendl_fd("exit", 1);
	error_status = exit_status;
	exit(exit_status);
}

