/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 13:56:01 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/21 19:03:35 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/execute.h"

void	straight_redirect(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("[ERROR]");
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	reverse_redirect(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("[ERROR]");
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	double_reverse_reirect(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("[ERROR]");
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	heredoc_print(t_list *cpy)
{
	int		i;
	char	**arr;

	i = 0;
	arr = ft_split(cpy->content, ' ');
	while (arr[i])
	{
		if (arr[i][0] == '$')
			printf("%s ", ft_env_search(&arr[i][1]));
		else
			printf("%s ", arr[i]);
		i++;
	}
	printf("\n");
	free_split(arr);
}

void	here_doc(char *del)
{
	char	*line;
	t_list	*lst;
	t_list	*cpy;

	dup2(0, STDIN_FILENO);
	lst = NULL;
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, del))
		{
			free(line);
			break ;
		}
		ft_lstadd_back(&lst, ft_lstnew(line));
	}
	cpy = lst;
	while (cpy != NULL)
	{
		lst = cpy;
		cpy = cpy->next;
		free(lst->content);
		free(lst);
	}
}
