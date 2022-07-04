/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:24:45 by gtaggana          #+#    #+#             */
/*   Updated: 2022/07/04 17:08:18 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/execute.h"

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
		g_shell->ret_stat = 0;
		ft_exit(EXIT_SUCCESS, 0);
	}
	else
	{
		cmd[0] = identify_cmd(cmd[0]);
		envp = convert_to_strarr(g_shell->env);
		g_shell->ret_stat = 0;
		execve(cmd[0], cmd, envp);
		g_shell->ret_stat = errno;
		perror(cmd[0]);
		free_split(envp);
		ft_exit(EXIT_FAILURE, 0);
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
	inter_sig();
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

void	solo_cmd_exe_helper(char **cmd)
{
	char	**envp;

	child_sig();
	cmd[0] = identify_cmd(cmd[0]);
	envp = convert_to_strarr(g_shell->env);
	g_shell->ret_stat = 0;
	execve(cmd[0], cmd, envp);
	g_shell->ret_stat = errno;
	perror(cmd[0]);
	free_split(envp);
	ft_exit(EXIT_FAILURE, 0);
}

void	solo_cmd_exe(char **cmd)
{
	int		*p_pid;

	if (builtin_parser(cmd, g_shell->env, g_shell->exp) != 0)
	{
		g_shell->ret_stat = 0;
		return ;
	}
	p_pid = malloc(sizeof(int));
	if (!p_pid)
		return ;
	*p_pid = fork();
	inter_sig();
	ft_lstadd_back(&g_shell->pids, ft_lstnew(p_pid));
	if (*p_pid == -1)
		perror("[ERROR]");
	else if (*p_pid == 0)
		solo_cmd_exe_helper(cmd);
	dup2(g_shell->std_in, STDIN_FILENO);
	dup2(g_shell->std_out, STDOUT_FILENO);
}
