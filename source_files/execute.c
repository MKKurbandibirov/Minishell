/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:42:18 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/07 14:59:54 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/execute.h"

void	child_proc(int *fd, char **cmd)
{
	char	**envp;

	child_sig();
	dup2(fd[0], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (builtin_parser(cmd, g_shell->env, g_shell->exp) == 0)
		exit(EXIT_SUCCESS);
	else
	{
		if (!identify_cmd(cmd[0]))
			perror("[ERROR]");
		envp = convert_to_strarr(g_shell->env);
		execve(cmd[0], cmd, envp);
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

// void	solo_cmd_exe()
// {
	
// }

// void	check_cmd(t_plist *curr)
// {
// 	while (curr != NULL)
// 	{
// 		if (curr->type == PIPE)

// 		curr = curr->next;
// 	}
// }

// t_cmds	*create_cmd_node(char **cmd, t_cmd_type type)
// {
// 	t_cmds	*node;

// 	node = malloc(sizeof(t_cmds));
// 	if (node)
// 		return (NULL);
// 	node->cmd = cmd;
// 	node->type = type;
// 	return (node);
// }

// t_list	*create_cmds(t_plist *line)
// {
// 	t_plist	*curr;
// 	t_list	*res;

// 	curr = line;
// 	res = NULL;
// 	while (curr != NULL)
// 	{
// 		if (curr->type == CMD)
// 			ft_lstadd_back(&res,
// 				ft_lstnew(create_cmd_node(create_cmd(curr), PIPE)));
// 		curr = curr->next;
// 	}
	
// }

int	ft_exe(t_plist *line)
{
	t_plist	*curr;

	curr = line;
	while (curr != NULL)
	{
		curr = curr->next;
	}
	return (0);
}
