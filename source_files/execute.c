/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:42:18 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/05/15 12:05:54 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/execute.h"

void	solo_cmd_exec(char **cmd, int fd_in, int fd_out)
{
	int		pid;
	char	**envp;

	(void)fd_in;
	(void)fd_out;
	envp = convert_to_strarr(g_shell->env);
	pid = fork();
	if (pid == -1)
		perror("[ERROR]");
	if (pid == 0)
	{
		child_sig();
		execve(cmd[0], cmd, envp);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &g_shell->return_status, 0);
	// printf("%d\n", g_shell->return_status);
}
