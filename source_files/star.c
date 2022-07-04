/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 15:52:08 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:09:07 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/minishell.h"

static int	match(char *pattern, char *candidate, int p, int c)
{
	if (pattern[p] == '\0')
		return (candidate[c] == '\0');
	else if (pattern[p] == '*')
	{
		while (candidate[c] != '\0')
		{
			if (match(pattern, candidate, p + 1, c))
				return (1);
			c++;
		}
		return (match(pattern, candidate, p + 1, c));
	}
	else if (pattern[p] != candidate[c])
		return (0);
	else
		return (match(pattern, candidate, p + 1, c + 1));
}

t_list	*replace_star(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			*cwdir;

	dir = opendir(g_shell->pwd);
	if (!dir)
		perror("[ERROR]");
	cwdir = NULL;
	while (1 && dir)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (entry->d_name[0] != '.' && match(pattern, entry->d_name, 0, 0))
			ft_lstadd_back(&cwdir, ft_lstnew(ft_strdup(entry->d_name)));
	}
	closedir(dir);
	return (cwdir);
}

void	free_simple_list(t_list *lst)
{
	t_list	*curr;

	while (lst)
	{
		curr = lst;
		free(lst->content);
		lst = lst->next;
		free(curr);
	}
	lst = NULL;
}

int	ft_count_elem_in_start(t_list *lst)
{
	t_list	*curr;
	int		i;

	i = 0;
	curr = lst;
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}
