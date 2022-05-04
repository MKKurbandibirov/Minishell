/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:27:53 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/05/04 14:40:04 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/builtins.h"

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
	exp_node->key= ft_substr(env_i, 0, j);
	if (option == 0)
	{
		exp_node->value = ft_substr(env_i, j + 1, ft_strlen(env_i) - j);
		exp_node->value = ft_strjoin_free("\"", exp_node->value, 2);
		exp_node->value = ft_strjoin_free(exp_node->value, "\"", 1);
	}
	exp_node->key = ft_strjoin_free("declare -x ", exp_node->key, 2);
	return (exp_node);
}

t_list	*get_expt(char **envr)
{
	int		i;
	t_list	*exp_list;
	exp_list = (t_list *)malloc(sizeof(t_list));
	if (!exp_list)
		return (NULL);
	i = 0;
	exp_list = NULL;
	while (envr[i + 1])
	{
		ft_lstadd_back(&exp_list, ft_lstnew(create_exp_node(envr[i], 0)));
		i++;
	}
	return (exp_list);
}

char	**convert_to_strarr(t_list *list)
{
	int		i;
	t_list	*curr;
	char	**strarr;
	
	printf("%d\n", ft_lstsize(curr));
	strarr = (char **)malloc(sizeof(char *) * (ft_lstsize(curr) + 1));
	if (!strarr)
		return (NULL);
	curr = list;
	i = 0;
	while (curr != NULL)
	{
		strarr[i] = ft_strjoin_free(ft_strjoin(((t_key_val *)curr->content)->key,
			"="), ((t_key_val *)curr->content)->value, 1);
		curr = curr->next;
		i++;
	}
	strarr[i] = NULL;
	return (strarr);
}

// char	**add_to_exp(char **exp, char *new)
// {
// 	int		len;
// 	int		i;
// 	char	**new_exp;

// 	len = 0;
// 	while (exp[len])
// 		len++;
// 	new_exp = (char **)malloc(sizeof(char *) * (len + 2));
// 	if (!new_exp)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		new_exp[i] = exp[i];
// 		i++;
// 	}
// 	new_exp[len] = new;
// 	new_exp[len + 1] = NULL;
// 	return (new_exp);
// }

int	ft_export(char **cmd, t_list *exp, t_list *env, int fd)
{
	int		i;
	char	**strarr;
	t_list	*curr = exp;

	if (cmd[1] == NULL)
	{
		i = -1;
		// strarr = convert_to_strarr(exp);
		while (curr != NULL)
		{
			write(fd, ((t_key_val *)curr->content)->key,
				ft_strlen(((t_key_val *)curr->content)->key));
			write(fd, ((t_key_val *)curr->content)->value,
				ft_strlen(((t_key_val *)curr->content)->value));
			
			// write(fd, strarr[i], ft_strlen(strarr[i]));
			write(fd, "\n", 1);
			curr = curr->next;
		}
	}
	// else if (ft_strnstr(cmd[1], "=", ft_strlen(cmd[1])))
	// {
	// 	// exp = add_to_exp(exp, create_exp_node(cmd[1], 0));
	// 	// // for (int i = 0; exp[i]; i++)
	// 	// // 	printf("%s\n", exp[i]);
	// 	ft_lstadd_back(&env, ft_lstnew(create_env_node(cmd[1])));
	// }
	// else if (cmd[1][0] == '-')
	// 	return (1);
	// else
	// 	ft_lstadd_back(&exp, ft_lstnew(create_exp_node(cmd[1], 1)));
	return (0);
}
