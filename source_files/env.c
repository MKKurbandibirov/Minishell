/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:24:54 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/05/03 15:40:04 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/builtins.h"

t_list	*get_envr(char **envr)
{
	int		i;
	int		j;
	t_env	*env;
	t_list	*env_list;
	t_list	*tmp;

	env_list = (t_list *)malloc(sizeof(t_list));
	i = 0;
	env_list = NULL;
	while (envr[i])
	{
		j = 0;
		while (envr[i][j] != '=')
			j++;
		env = (t_env *)malloc(sizeof(t_env));
		env->key = ft_substr(envr[i], 0, j);
		env->value = ft_substr(envr[i], j + 1, ft_strlen(envr[i]) - j);
		tmp = ft_lstnew(env);
		ft_lstadd_back(&env_list, tmp);
		i++;
	}
	return (env_list);
}

void	ft_env(t_list *my_env, int fd)
{
	t_list	*curr;

	curr = my_env;
	while (curr->next != NULL)
	{
		write(fd, ((t_env *)curr->content)->key,
			ft_strlen(((t_env *)curr->content)->key));
		write(fd, "=", 1);
		write(fd, ((t_env *)curr->content)->value,
			ft_strlen(((t_env *)curr->content)->value));
		write(fd, "\n", 1);
		curr = curr->next;
	}
}
