/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:48:33 by jonhan            #+#    #+#             */
/*   Updated: 2023/08/09 13:48:34 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_getenvnode(t_list **environ, char *word)
{
	t_list	*iter;
	char	*new_word;

	iter = *environ;
	while (iter)
	{
		if (!ft_strcmp(iter->content, word))
			return (iter);
		iter = iter->next;
	}
	new_word = ft_strjoin(word, "=");
	iter = *environ;
	while (iter)
	{
		if (!ft_strncmp(iter->content, new_word, ft_strlen(new_word)))
			return (iter);
		iter = iter->next;
	}
	return (NULL);
}

void	ft_unset(char **simple_cmd, t_list **environ, int fd)
{
	t_list	*tmp;
	int		i;

	(void)fd;
	i = 0;
	tmp = NULL;
	error_status = 0;
	while (simple_cmd[++i])
	{
		tmp = ft_getenvnode(environ, simple_cmd[i]);
		if (tmp)
			ft_lstdel_mid(environ, tmp);
	}
}
