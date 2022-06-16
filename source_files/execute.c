/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:42:18 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/16 15:54:27 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/execute.h"

void	child_proc(int *fd, char **cmd)
{
	char	**envp;

	child_sig();
	close(STDOUT_FILENO);
	dup2(fd[0], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (builtin_parser(cmd, g_shell->env, g_shell->exp) != 0)
	{
		g_shell->return_status = 0;
		exit(EXIT_SUCCESS);
	}
	else
	{
		identify_cmd(cmd[0]);
		envp = convert_to_strarr(g_shell->env);
		g_shell->return_status = 0;
		execve(cmd[0], cmd, envp);
		g_shell->return_status = errno;
		perror("[ERROR]");
		exit(EXIT_FAILURE);
	}
}

void	ft_pipe(char **cmd)
{
	int	fd[2];
	int	pid;

	pipe(fd);
	pid = fork();
	if (pid == -1)
		perror("[ERROR]");
	if (pid == 0)
		child_proc(fd, cmd);
	free_split(cmd);
	close(STDIN_FILENO);
	dup2(fd[1], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}

char	**create_cmd(t_plist *node)
{
	t_plist	*curr;
	char	**cmd;
	int		i;
	int		len;

	curr = node;
	len = 0;
	while (curr->type != CMD)
	{
		curr = curr->prev;
		len++;
	}
	cmd = malloc(sizeof(char *) * (len + 1));
	if (!cmd)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		cmd[i] = strdup(curr->data);
		curr = curr->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

void	solo_cmd_exe(char **cmd)
{
	int		pid;
	char	**envp;

	pid = fork();
	if (pid == -1)
		perror("[ERROR]");
	if (pid == 0)
	{
		child_sig();
		if (builtin_parser(cmd, g_shell->env, g_shell->exp) != 0)
		{
			g_shell->return_status = 0;
			exit(EXIT_SUCCESS);
		}
		else
		{
			identify_cmd(cmd[0]);
			envp = convert_to_strarr(g_shell->env);
			g_shell->return_status = 0;
			execve(cmd[0], cmd, envp);
			g_shell->return_status = errno;
			perror("[ERROR]");
			exit(EXIT_FAILURE);
		}
	}
}

int	ft_exe(t_plist *line)
{
	t_plist	*curr;

	curr = line;
	while (curr != NULL)
	{
		if (curr->type == PIPE)
			ft_pipe(create_cmd(curr));
		curr = curr->next;
	}
	return (0);
}
