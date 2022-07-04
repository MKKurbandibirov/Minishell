/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 08:46:35 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:08:12 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/builtins.h"

void	unset_from_env(t_list *env, char *var)
{
	t_list	*curr;

	curr = env;
	while (curr != NULL)
	{
		if (!ft_strcmp(((t_key_val *)curr->content)->key, var))
			ft_lstdelone(&env, curr);
		curr = curr->next;
	}
}

void	unset_from_exp(t_list *exp, char *var)
{
	t_list	*curr;
	char	*tmp;

	tmp = ft_strjoin("declare -x ", var);
	curr = exp;
	while (curr != NULL)
	{
		if (!ft_strcmp(((t_key_val *)curr->content)->key, tmp))
			ft_lstdelone(&exp, curr);
		curr = curr->next;
	}
	free(tmp);
}

int	ft_unset(t_list *env, t_list *exp, char **vars)
{
	int	i;

	i = 1;
	if (vars[i][0] == '-')
		return (1);
	while (vars[i])
	{
		unset_from_env(env, vars[i]);
		unset_from_exp(exp, vars[i]);
		i++;
	}
	return (0);
}
