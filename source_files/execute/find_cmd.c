/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:15:21 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:02:58 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/execute.h"

void	path_parse(void)
{
	t_list	*curr;
	int		i;

	curr = g_shell->env;
	while (curr != NULL)
	{
		if (!ft_strcmp(((t_key_val *)curr->content)->key, "PATH"))
			break ;
		curr = curr->next;
	}
	if (curr == NULL)
	{
		write(2, "[ERROR]: No such file or directory\n", 35);
		g_shell->cmd_path = NULL;
		return ;
	}
	g_shell->cmd_path = ft_split(((t_key_val *)curr->content)->val, ':');
	i = 0;
	while (g_shell->cmd_path[i])
	{
		g_shell->cmd_path[i] = ft_strjoin_free(g_shell->cmd_path[i], "/", 1);
		i++;
	}
}

char	*identify_cmd(char *cmd)
{
	int		i;
	char	*abs_cmd;

	i = -1;
	if (!cmd || !g_shell->cmd_path)
		return (NULL);
	while (g_shell->cmd_path[++i])
	{
		abs_cmd = ft_strjoin(g_shell->cmd_path[i], cmd);
		if (access(abs_cmd, F_OK) == 0)
		{
			free(cmd);
			return (abs_cmd);
		}
		else
			free(abs_cmd);
	}
	return (cmd);
}
