/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:42:18 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/21 14:26:27 by nfarfetc         ###   ########.fr       */
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
	tmp_sig();
	ft_lstadd_back(&g_shell->pids, ft_lstnew(p_pid));
	if (*p_pid == -1)
		perror("[ERROR]");
	else if (*p_pid == 0)
		child_proc(fd, cmd);
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
	dup2(g_shell->std_in, STDIN_FILENO);
	dup2(g_shell->std_out, STDOUT_FILENO);
}

void	ft_exe(void)
{
	int	status;

	while (g_shell->master != NULL)
	{
		while (g_shell->master->content != NULL)
		{
			if (g_shell->master->content->type == PIPE)
				ft_pipe(g_shell->master->content->cmd);
			else if (g_shell->master->content->type == CMD)
				solo_cmd_exe(g_shell->master->content->cmd);
			ft_delelem_s(&g_shell->master->content, g_shell->master->content);
		}
		ft_delelem_m(&g_shell->master, g_shell->master);
	}
	while (g_shell->pids)
	{
		status = g_shell->return_status;
		waitpid(*(int *)g_shell->pids->content, &status, 0);
		g_shell->pids = g_shell->pids->next;
	}
	if (g_shell->return_status != status)
		g_shell->return_status = WEXITSTATUS(status);
	dup2(g_shell->std_in, STDIN_FILENO);
	dup2(g_shell->std_out, STDOUT_FILENO);
}
