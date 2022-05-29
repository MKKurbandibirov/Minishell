/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:42:51 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/05/29 11:43:17 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "./minishell.h"

typedef struct s_pipe
{
	char	***cmd;
	int		*pipe_fd;
	pid_t	*pid;
	int		*status;
	int		cmd_count;
}	t_pipe;

void	path_parse(void);
char	*identify_cmd(char *cmd);
void	solo_cmd_exec(char **cmd, int fd_in, int fd_out, t_pipe *pipel);

void	ft_pipe(char ***cmd, int cmd_count, int fd_in, int fd_out);
#endif