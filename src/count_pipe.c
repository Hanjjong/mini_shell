/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:43:47 by jonhan            #+#    #+#             */
/*   Updated: 2023/08/09 14:43:52 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipe(t_cmd **pipeline)
{
	t_cmd	*iter;
	int		cnt;

	cnt = 0;
	iter = *pipeline;
	while (iter)
	{
		cnt++;
		iter = iter->next;
	}
	return (cnt);
}
