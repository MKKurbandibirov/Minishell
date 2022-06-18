/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 15:52:08 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/18 16:49:55 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/minishell.h"

static t_list	*create_list_of_entrance(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			*cwdir;
	int				l;

	dir = opendir(g_shell->pwd);
	if (!dir)
		perror("[ERROR]");
	cwdir = NULL;
	l = ft_strlen(pattern);
	while (1 && dir)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (pattern[0] == '*' && pattern[l - 1] == '*')
		{
			if (ft_substr(entry->d_name, )
		}
		ft_lstadd_back(&cwdir, ft_lstnew(ft_strdup()));
	}
	closedir(dir);
	return (cwdir);
}

static t_list	*choose_for_pattern(t_list *cwdir, char *pattern)
{
	int	l;

	l = ft_strlen(pattern);
	if (pattern[0] == '*' && pattern[l - 1] == '*')
	{
		t_list	*curr;

		curr = cwdir;
		while (curr != NULL)
		{
			if (ft_substr() curr->content)
			curr = curr->next;
		}
	}
}

void	replace_star(char *pattern)
{
	t_list	*cwdir;

	cwdir = create_list_of_entrance();
	
}
