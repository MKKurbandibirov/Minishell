/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 13:56:01 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/22 12:03:24 by nfarfetc         ###   ########.fr       */
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
	while (arr && arr[i])
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

void	heredoc_init(char *del)
{
	char	*line;
	t_list	*lst;

	// dup2(g_shell->std_in, STDIN_FILENO);
	tmp_sig();
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
	heredoc_print(lst);
}

void	heredoc(char *del)
{
	int		pid;
	int		fd[2];
	int		status;

	if (pipe(fd) == -1)
		return ;
	pid = fork();
	child_sig();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		perror("[ERROR]");
		return ;
	}
	if (pid == 0)
	{
		heredoc_init(del);
		exit(1);
	}
	waitpid(pid, &status, 0);
	close(fd[1]);
}
