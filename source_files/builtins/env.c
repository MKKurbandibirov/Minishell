/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:24:54 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:08:03 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/builtins.h"

t_key_val	*create_env_node(char *env_i)
{
	int			pos;
	t_key_val	*env;

	pos = 0;
	while (env_i[pos] != '=')
		pos++;
	env = (t_key_val *)malloc(sizeof(t_key_val));
	if (!env)
		return (NULL);
	env->key = ft_substr(env_i, 0, pos);
	env->val = ft_substr(env_i, pos + 1, ft_strlen(env_i) - pos);
	env->val = ft_strtrim(env->val, "\"\'");
	return (env);
}

t_list	*get_envr(char **envr)
{
	int		i;
	t_list	*env_list;

	i = -1;
	env_list = NULL;
	while (envr[++i])
		ft_lstadd_back(&env_list, ft_lstnew(create_env_node(envr[i])));
	return (env_list);
}

void	ft_env(t_list *my_env)
{
	t_list	*curr;

	curr = my_env;
	while (curr != NULL)
	{
		printf("%s=%s\n", ((t_key_val *)curr->content)->key,
			((t_key_val *)curr->content)->val);
		curr = curr->next;
	}
}
