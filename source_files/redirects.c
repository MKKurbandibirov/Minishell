/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 13:56:01 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/25 10:49:05 by nfarfetc         ###   ########.fr       */
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

//--------------------------------------------------------
// Дописать это говно!
void	heredoc_print(t_list *cpy, int fd)
{
	int		i;
	char	**arr;

	i = 0;
	arr = ft_split(cpy->content, ' ');
	while (arr && arr[i])
	{
		if (arr[i][0] == '$')
			ft_putstr_fd(ft_env_search(&arr[i][1]), fd);
		else
			ft_putstr_fd(arr[i], fd);
		i++;
	}
	ft_putchar_fd('\n', fd);
	close(fd);
	free_split(arr);
	free_simple_list(cpy);
}

void	heredoc_init(char *del, int fd)
{
	char	*line;
	t_list	*lst;

	inter_sig();
	lst = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, del))
		{
			free(line);
			break ;
		}
		ft_lstadd_back(&lst, ft_lstnew(line));
	}
	heredoc_print(lst, fd);
}

void	heredoc(char *del)
{
	int		pid;
	int		fd[2];
	int		status;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		child_sig();
		if (pipe(fd) == -1)
			exit(1);
		close(fd[1]);
		heredoc_init(del, fd[0]);
		exit(0);
	}
	waitpid(pid, &status, 0);
	g_shell->return_status = status;
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
}
