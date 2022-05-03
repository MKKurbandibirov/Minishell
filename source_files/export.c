/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:27:53 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/05/03 16:48:45 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/builtins.h"

void	str_bubble(char **arr, int len)
{
	int		i;
	int		j;
	char	*tmp;

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

char	**exp_sort(char **envr)
{
	int		i;
	int		len;
	char	**sorted;

	len = 0;
	while (envr[len])
		len++;
	sorted = malloc(sizeof(char *) * (len + 1));
	i = -1;
	while (envr[++i])
		sorted[i] = ft_strdup(envr[i]);
	str_bubble(sorted, len);
	// printf("%s\n", sorted[len - 1]);
	sorted[len] = NULL;
	return (sorted);
}

char	*helper(char *env_i)
{
	char	*key;
	char	*val;
	int		j;

	j = 0;
	while (env_i[j] != '=')
		j++;
	key = ft_substr(env_i, 0, j);
	val = ft_substr(env_i, j + 1, ft_strlen(env_i) - j);
	val = ft_strjoin_free("\"", val, 2);
	val = ft_strjoin_free(val, "\"", 1);
	key = ft_strjoin_free("declare -x ", key, 2);
	key = ft_strjoin_free(key, "=", 1);
	key = ft_strjoin_free(key, val, 3);
	return (key);
}

t_list	*get_expt(char **envr)
{
	int		i;
	t_list	*exp_list;
	t_list	*tmp;

	i = 0;
	exp_list = (t_list *)malloc(sizeof(t_list));
	exp_list = NULL;
	while (envr[i])
	{
		if (!ft_strnstr(envr[i], "_=", 2))
		{
			tmp = ft_lstnew(helper(envr[i]));
			ft_lstadd_back(&exp_list, tmp);
		}
		i++;
	}
	return (exp_list);
}

int	ft_export(char **cmd, t_list *exp, int fd)
{
	t_list	*curr;

	curr = exp;
	while (curr != NULL)
	{
		write(fd, curr->content, ft_strlen(curr->content));
		write(fd, "\n", 1);
		curr = curr->next;
	}
	return (0);
}
