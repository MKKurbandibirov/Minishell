/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:42:18 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/06 15:05:53 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/execute.h"

void	fd_close(t_pipe *pipel)
{
	int	i;

	i = -1;
	while (++i < (pipel->cmd_count - 1) * 2)
		close(pipel->pipe_fd[i]);
	// if (!pipel->del)
	// 	close(pipel->file_fd[0]);
	// close(pipel->file_fd[1]);
}

void	solo_cmd_exec(char **cmd, int fd_in, int fd_out, t_pipe *pipel)
{
	int		pid;
	char	**envp;

	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	envp = convert_to_strarr(g_shell->env);
	pid = fork();
	if (pid == -1)
		perror("[ERROR]");
	if (pid == 0)
	{
		child_sig();
		if (pipel)
			fd_close(pipel);
		execve(cmd[0], cmd, envp);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &g_shell->return_status, 0);
}

t_pipe	*init_pipeline(int cmd_count)
{
	int		i;
	t_pipe	*pipel;

	pipel = malloc(sizeof(t_pipe));
	pipel->cmd_count = cmd_count;
	pipel->pid = malloc(sizeof(pid_t) * cmd_count);
	pipel->status = malloc(sizeof(int) * cmd_count);
	pipel->pipe_fd = malloc(sizeof(int) * (cmd_count * 2));
	if (!(pipel && pipel->pid && pipel->pipe_fd && pipel->status))
		return (NULL);
	i = -1;
	while (++i < pipel->cmd_count - 1)
		if (pipe(pipel->pipe_fd + i * 2) == -1)
			return (NULL);
	return (pipel);
}

void	child_proc(char **cmd, int fd_in, int fd_out, t_pipe *pipel)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	fd_close(pipel);
	printf("cmd now - %s\n", cmd[0]);
	execve(cmd[0], cmd, NULL);
	printf("Error: execve error!");
	exit(EXIT_FAILURE);
}

void	ft_pipe(char ***cmd, int cmd_count, int fd_in, int fd_out)
{
	int		i;
	t_pipe	*pipel;

	i = -1;
	pipel = init_pipeline(cmd_count);
	if (!pipel)
		return ; // Error
	pipel->cmd = cmd;
	while (++i < pipel->cmd_count)
	{
		pipel->pid[i] = fork();
		if (pipel->pid[i] == -1)
			return ; // Error
		if (pipel->pid[i] == 0)
		{
			if (i == 0)
				child_proc(pipel->cmd[i], fd_in, pipel->pipe_fd[i * 2 + 1], pipel);
			else if (i == pipel->cmd_count - 1)
				child_proc(pipel->cmd[i], pipel->pipe_fd[2 * i - 2], fd_out, pipel);
			else
				child_proc(pipel->cmd[i], pipel->pipe_fd[2 * i - 2], pipel->pipe_fd[i * 2 + 1], pipel);
		}
	}
	i = -1;
	fd_close(pipel);
	while (++i < pipel->cmd_count)
		waitpid(pipel->pid[i], &pipel->status[i], WNOHANG);
}
