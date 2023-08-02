#include "minishell.h"

int	is_delim(char c)
{
	return (c == '$' || c == '\'' || c == '\"');
}

void	expansion(t_list *node, char *content, int *idx, t_list **environ)
{
	t_list	*lst;
	char	*str;
	char	*env;
	int		key_size;
	int		q_flag;
	int		i;

	lst = NULL;
	i = 0;
	q_flag = 0;
	while (content[i])
	{
		key_size = 0;
		if (content[i + key_size] == '$' && q_flag != '\'')
		{
			i++;
			while (content[i + key_size] && !is_delim(content[i + key_size]))
			{
				if (q_flag == '\"' && (ft_is_blank(content[i + key_size]) \
					|| content[i + key_size] == '$'))
					break ;
				key_size++;
			}
			str = ft_substr(content, i, key_size);
			env = ft_getenv(environ, str);
			if (env == NULL && !ft_strncmp(str, "?", 1))
				env = ft_strjoin("0", ft_substr(str, 1, ft_strlen(str))); // 0 -> exit_status_itoa 구현, substring leak 관리
			else if (env == NULL && key_size != 0)
				env = ft_strdup("");
			else if (env == NULL && key_size == 0)
				env = ft_strdup("$");
			free(str);
			ft_lstadd_back(&lst, ft_lstnew(env));
			i += key_size;
		}
		else if (content[i + key_size] == '\'')
		{
			if (q_flag == 0)
				q_flag = '\'';
			else if (q_flag == '\'')
				q_flag = 0;
			ft_lstadd_back(&lst, ft_lstnew(ft_strdup("\'")));
			i++;
		}
		else if (content[i + key_size] == '\"')
		{
			if (q_flag == 0)
				q_flag = '\"';
			else if (q_flag == '\"')
				q_flag = 0;
			ft_lstadd_back(&lst, ft_lstnew(ft_strdup("\"")));
			i++;
		}
		else
		{
			while (content[i + key_size]
				&& !ft_strchr("\'\"", content[i + key_size]))
			{
				if (q_flag != '\'' && content[i + key_size] == '$')
					break ;
				key_size++;
			}
			str = ft_substr(content, i, key_size);
			ft_lstadd_back(&lst, ft_lstnew(str));
			i += key_size;
		}
	}
	*idx = i;
	free(node->content);
	node->content = ft_lst_strjoin(&lst);
	ft_lstclear(&lst, free);
}

char	*ft_lst_strjoin(t_list **lst)
{
	t_list	*iter;
	char	*res;
	char	*tmp;

	res = ft_strdup((char *)(*lst)->content);
	iter = (*lst)->next;
	tmp = 0;
	while (iter)
	{
		tmp = res;
		res = ft_strjoin(res, iter->content);
		free(tmp);
		iter = iter->next;
	}
	return (res);
}