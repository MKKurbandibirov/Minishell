/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:27:53 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:08:08 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/builtins.h"

static void	helper(t_list *curr, t_key_val *node)
{
	if (((t_key_val *)curr->content)->val != NULL
		&& node->val == NULL)
	{
		free(node);
	}
	else
	{
		free(((t_key_val *)curr->content)->key);
		free(((t_key_val *)curr->content)->val);
		free(curr->content);
		curr->content = node;
	}
}

void	exp_check(t_list *exp, char *cmd_1, int option)
{
	t_list		*curr;
	t_key_val	*node;

	curr = exp;
	node = create_exp_node(cmd_1, option);
	if (!node)
		return ;
	while (curr != NULL)
	{
		if (!ft_strcmp(((t_key_val *)curr->content)->key, node->key))
			break ;
		curr = curr->next;
	}
	if (curr != NULL)
	{
		helper(curr, node);
	}
	else
		ft_lstadd_back(&exp, ft_lstnew(node));
}

void	env_check(t_list *env, char *cmd_i)
{
	t_list		*curr;
	t_key_val	*node;

	curr = env;
	node = create_env_node(cmd_i);
	while (curr != NULL)
	{
		if (!ft_strcmp(((t_key_val *)curr->content)->key, node->key))
			break ;
		curr = curr->next;
	}
	if (curr != NULL)
	{
		if (node->val[0] != '\0')
		{
			free(((t_key_val *)curr->content)->key);
			free(((t_key_val *)curr->content)->val);
			free(curr->content);
			curr->content = node;
		}
	}
	else
		ft_lstadd_back(&env, ft_lstnew(node));
}

int	ft_export(char *cmd_1, t_list *exp, t_list *env)
{
	int		i;
	char	**strarr;

	if (cmd_1 == NULL)
	{
		i = -1;
		strarr = convert_to_strarr(exp);
		str_bubble(strarr);
		while (strarr[++i])
			printf("%s\n", strarr[i]);
		free_split(strarr);
	}
	else if (ft_strnstr(cmd_1, "=", ft_strlen(cmd_1)))
	{
		exp_check(exp, cmd_1, 0);
		env_check(env, cmd_1);
	}
	else if (cmd_1[0] == '-')
		return (1);
	else
		exp_check(exp, cmd_1, 1);
	return (0);
}
