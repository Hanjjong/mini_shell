/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:27:55 by jonhan            #+#    #+#             */
/*   Updated: 2023/08/09 13:44:30 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cd_err(char *path, char *str)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(str, 2);
	error_status = 1;
}

int	update_pwd(t_list ***environ)
{
	char	*getcwdstr;
	t_list	*tmp;

	getcwdstr = getcwd(NULL, 0);
	if (getcwdstr == NULL)
	{
		ft_putstr_fd("cd: error retrieving current directory: \
			 getcwd: cannot access parent ", 2);
		perror("directories");
		return (1);
	}
	tmp = ft_getenvnode(*environ, "PWD");
	if (tmp == NULL)
		return (1);
	free(tmp->content);
	tmp->content = ft_strjoin("PWD=", getcwdstr);
	return (0);
}

void	ft_cd(char **simple_cmd, t_list **environ, int fd)
{
	char	*pathname;
	int		ch;

	(void)fd;
	error_status = 0;
	if (simple_cmd[1])
		pathname = simple_cmd[1];
	else
	{
		pathname = ft_getenv(environ, "HOME");
		if (pathname == NULL)
		{
			print_cd_err("HOME", "not set");
			return ;
		}
	}
	ch = chdir(pathname);
	if (ch < 0)
		print_cd_err(pathname, "No such file or directory");
	else
	{
		if (update_pwd(&environ) == 0)
			return ;
	}
}




