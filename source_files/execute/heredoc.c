/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:24:52 by gtaggana          #+#    #+#             */
/*   Updated: 2022/07/04 17:08:24 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/execute.h"

static void	heredoc_print(void)
{
	int		fd;

	fd = open("heredoc", O_RDONLY);
	if (fd == -1)
		return ;
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static int	heredoc_init(char *del, int fd)
{
	char	*line;
	char	*tmp;

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
		tmp = ft_here_dollar(line);
		ft_putendl_fd(tmp, fd);
	}
	close(fd);
	return (0);
}

void	heredoc(char *del)
{
	int	fd;
	int	pid;
	int	status;

	fd = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	pid = fork();
	inter_sig();
	if (pid == 0)
	{
		child_sig();
		if (heredoc_init(del, fd))
			ft_exit(EXIT_FAILURE, 0);
		ft_exit(EXIT_SUCCESS, 0);
	}
	waitpid(pid, &status, 0);
	close(fd);
	heredoc_print();
	unlink("heredoc");
}
