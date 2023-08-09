/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:45:06 by jonhan            #+#    #+#             */
/*   Updated: 2023/08/09 13:47:40 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_more_newline(char **simple_cmd)
{
	int	i;

	i = 2;
	while (simple_cmd[i] != NULL)
	{
		if (simple_cmd[i] != NULL && !ft_strcmp("-n", simple_cmd[i]))
			i++;
		else
			break ;
	}
	return (i);
}

void	ft_echo(char **simple_cmd, t_list **environ, int fd)
{
	int	i;

	error_status = 0;
	if (!environ)
		return ;
	if (simple_cmd[1] != NULL && !ft_strcmp("-n", simple_cmd[1]))
	{
		i = check_more_newline(simple_cmd);
		while (simple_cmd[i] != NULL)
		{
			ft_putstr_fd(simple_cmd[i], fd);
			if (simple_cmd[i + 1] != NULL)
				ft_putstr_fd(" ", fd);
			i++;
		}
		return ;
	}
	i = 0;
	while (simple_cmd[++i] != NULL)
	{
		ft_putstr_fd(simple_cmd[i], fd);
		if (simple_cmd[i + 1] != NULL)
			ft_putstr_fd(" ", fd);
	}
	write(fd, "\n", 1);
}
