/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 13:56:01 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:08:27 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/execute.h"

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
