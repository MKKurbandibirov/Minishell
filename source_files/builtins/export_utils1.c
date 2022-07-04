/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:19:51 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:08:05 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/builtins.h"

void	str_bubble(char **arr)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	len = 0;
	while (arr[len])
		len++;
	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				tmp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

t_key_val	*create_exp_node(char *env_i, int option)
{
	t_key_val	*exp_node;
	int			j;

	j = 0;
	while (env_i[j] != '=' && env_i[j])
		j++;
	exp_node = (t_key_val *)malloc(sizeof(t_key_val));
	if (!exp_node)
		return (NULL);
	exp_node->key = ft_substr(env_i, 0, j);
	if (exp_node->key == NULL)
		return (NULL);
	if (option == 0)
	{
		exp_node->val = ft_substr(env_i, j + 1, ft_strlen(env_i) - j);
		exp_node->val = ft_strjoin_free(ft_strdup("\""), exp_node->val, 3);
		exp_node->val = ft_strjoin_free(exp_node->val, ft_strdup("\""), 3);
	}
	else
		exp_node->val = NULL;
	exp_node->key = ft_strjoin_free(ft_strdup("declare -x "), exp_node->key, 3);
	return (exp_node);
}

t_list	*get_expt(char **envr)
{
	int		i;
	t_list	*exp_list;

	i = 0;
	exp_list = NULL;
	while (envr[i + 1])
	{
		ft_lstadd_back(&exp_list, ft_lstnew(create_exp_node(envr[i], 0)));
		i++;
	}
	return (exp_list);
}

void	fill(t_list *c, char **s_arr)
{
	int		i;
	char	*tmp;

	i = 0;
	while (c != NULL)
	{
		if (((t_key_val *)c->content)->val != NULL)
		{
			tmp = ft_strjoin(((t_key_val *)c->content)->key, "=");
			s_arr[i] = ft_strjoin_free(tmp, ((t_key_val *)c->content)->val, 1);
		}
		else
			s_arr[i] = ft_strdup(((t_key_val *)c->content)->key);
		c = c->next;
		i++;
	}
	s_arr[i] = NULL;
}

char	**convert_to_strarr(t_list *list)
{
	int		i;
	t_list	*curr;
	char	**strarr;

	i = 0;
	curr = list;
	while (curr != NULL)
	{
		curr = curr->next;
		i++;
	}
	strarr = (char **)malloc(sizeof(char *) * (i + 1));
	if (!strarr)
		return (NULL);
	i = 0;
	curr = list;
	fill(curr, strarr);
	return (strarr);
}
