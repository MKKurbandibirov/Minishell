/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 16:01:33 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/02 13:01:58 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/execute.h"

//--------------------------------------------------------
//					Дописать это говно!
static void	heredoc_print(t_list *cpy, int fd)
{
	char	*tmp;
	t_list	*curr;

	curr = cpy;
	while (curr != NULL)
	{
		tmp = ft_here_dollar(curr->content);
		ft_putendl_fd(tmp, g_shell->std_out);
		free(tmp);
		curr = curr->next;
	}
	close(fd);
	free_simple_list(cpy);
}

static int	heredoc_init(char *del, int fd)
{
	char	*line;
	t_list	*lst;

	lst = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (1);
		if (!ft_strcmp(line, del))
		{
			free(line);
			break ;
		}
		ft_lstadd_back(&lst, ft_lstnew(line));
	}
	heredoc_print(lst, fd);
	return (0);
}

void	heredoc(char *del)
{
	int		pid;
	int		fd[2];
	int		status;

	pid = fork();
	if (pid < 0)
		return ;
	if (pipe(fd) == -1)
		return ;
	inter_sig();
	if (pid == 0)
	{
		child_sig();
		close(fd[0]);
		if (heredoc_init(del, fd[1]) == 1)
		{
			g_shell->ret_stat = 1;
			exit(1);
		}
		exit(0);
	}
	waitpid(pid, &status, 0);
	g_shell->ret_stat = status;
	dup2(fd[0], STDIN_FILENO);
	// dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}
