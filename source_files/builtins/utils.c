/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:36:44 by magomed           #+#    #+#             */
/*   Updated: 2022/05/29 11:38:10 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/builtins.h"

int	norm_helper(char **cmd, t_list *env, t_list *exp)
{
	if (!ft_strcmp("env", cmd[0]) && cmd[1] == NULL)
	{
		ft_env(env, 0);
		return (1);
	}
	else if (!ft_strcmp("export", cmd[0]) && !ft_export(cmd[1], exp, env, 0))
		return (1);
	else if (!ft_strcmp("unset", cmd[0]) && !ft_unset(env, exp, cmd))
		return (1);
	else if (!ft_strcmp("exit", cmd[0]) && cmd[1] == NULL)
	{
		ft_exit();
		return (1);
	}
	return (0);
}

int	builtin_parser(char **cmd, t_list *env, t_list *exp)
{
	if (!ft_strcmp("echo", cmd[0]) && !ft_echo_n(cmd, 0))
		return (1);
	else if (!ft_strcmp("pwd", cmd[0]) && cmd[1] == NULL)
	{
		ft_pwd(0);
		return (1);
	}
	else if (!ft_strcmp("cd", cmd[0]))
	{
		if (cmd[1] == NULL)
			ft_cd("", env, exp, 0);
		else
			ft_cd(cmd[1], env, exp, 0);
		return (1);
	}
	else if (norm_helper(cmd, env, exp))
		return (1);
	return (0);
}

void	free_list(t_list *lst)
{
	t_list	*curr;

	curr = lst;
	while (curr != NULL)
	{
		free(((t_key_val *)curr->content)->key);
		free(((t_key_val *)curr->content)->val);
		free((t_key_val *)curr->content);
		curr = curr->next;
		free(lst);
		lst = curr;
	}
	free(curr);
	free(lst);
}
