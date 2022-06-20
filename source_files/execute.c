/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:42:18 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/18 15:51:55 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/execute.h"

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

void	child_proc(int *fd, char **cmd)
{
	char	**envp;

	child_sig();
	close(STDOUT_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (builtin_parser(cmd, g_shell->env, g_shell->exp) != 0)
	{
		g_shell->return_status = 0;
		ft_exit(EXIT_SUCCESS);
	}
	else
	{
		cmd[0] = identify_cmd(cmd[0]);
		envp = convert_to_strarr(g_shell->env);
		g_shell->return_status = 0;
		execve(cmd[0], cmd, envp);
		g_shell->return_status = errno;
		perror("[ERROR]");
		free_split(envp);
		ft_exit(EXIT_FAILURE);
	}
}

void	ft_pipe(char **cmd)
{
	int	fd[2];
	int	*p_pid;

	pipe(fd);
	p_pid = malloc(sizeof(int));
	if (!p_pid)
		return ;
	*p_pid = fork();
	ft_lstadd_back(&g_shell->pids, ft_lstnew(p_pid));
	if (*p_pid == -1)
		perror("[ERROR]");
	else if (*p_pid == 0)
		child_proc(fd, cmd);
	free_split(cmd);
	close(STDIN_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}

void	solo_cmd_exe(char **cmd)
{
	int		*p_pid;
	char	**envp;

	if (builtin_parser(cmd, g_shell->env, g_shell->exp) != 0)
	{
		g_shell->return_status = 0;
		return ;
	}
	p_pid = malloc(sizeof(int));
	if (!p_pid)
		return ;
	*p_pid = fork();
	ft_lstadd_back(&g_shell->pids, ft_lstnew(p_pid));
	if (*p_pid == -1)
		perror("[ERROR]");
	else if (*p_pid == 0)
	{
		child_sig();
		cmd[0] = identify_cmd(cmd[0]);
		envp = convert_to_strarr(g_shell->env);
		g_shell->return_status = 0;
		execve(cmd[0], cmd, envp);
		g_shell->return_status = errno;
		perror("[ERROR]");
		free_split(envp);
		ft_exit(EXIT_FAILURE);
	}
}

void	ft_exe(void)
{
	int	*status;

	while (g_shell->master != NULL)
	{
		while (g_shell->master->content != NULL)
		{
			if (g_shell->master->content->type == PIPE)
				ft_pipe(g_shell->master->content->cmd);
			else if (g_shell->master->content->type == CMD)
				solo_cmd_exe(g_shell->master->content->cmd);
			g_shell->master->content = g_shell->master->content->next;
		}
		g_shell->master = g_shell->master->next;
	}
	while (g_shell->pids)
	{
		status = malloc(sizeof(int));
		if (!status)
			return ;
		waitpid(*(int *)g_shell->pids->content, status, WNOHANG);
		ft_lstadd_back(&g_shell->status, ft_lstnew(status));
		g_shell->pids = g_shell->pids->next;
	}
	dup2(STDIN_FILENO, 0);
	dup2(STDOUT_FILENO, 1);
}
