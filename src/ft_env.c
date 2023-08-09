/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:47:51 by jonhan            #+#    #+#             */
/*   Updated: 2023/08/09 13:47:53 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **simple_cmd, t_list **environ, int fd)
{
	t_list	*iter;

	error_status = 0;
	if (!simple_cmd)
		return ;
	iter = *environ;
	while (iter)
	{
		if (ft_strchr(iter->content, '='))
			ft_putendl_fd(iter->content, fd);
		iter = iter->next;
	}
}
