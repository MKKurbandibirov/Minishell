/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:42:18 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/25 16:15:15 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/execute.h"

void	ft_exe(void)
{
	int	status;

	while (g_shell->master != NULL)
	{
		while (g_shell->master->content != NULL)
		{
			replace_status(g_shell->master->content->cmd);
			if (g_shell->master->content->type == PIPE)
				ft_pipe(g_shell->master->content->cmd);
			else if (g_shell->master->content->type == CMD)
				solo_cmd_exe(g_shell->master->content->cmd);
			else if (g_shell->master->content->type == INFILE_RE)
				straight_redirect(g_shell->master->content->cmd[0]);
			else if (g_shell->master->content->type == OUTFILE_RE)
			{
				reverse_redirect(g_shell->master->content->cmd[0]);
				if (g_shell->master->content->next->type == PIPE)
					g_shell->master->content->next->type = CMD;
			}
			else if (g_shell->master->content->type == APPEND)
			{
				double_reverse_reirect(g_shell->master->content->cmd[0]);
				if (g_shell->master->content->next->type == PIPE)
					g_shell->master->content->next->type = CMD;
			}
			else if (g_shell->master->content->type == HEREDOC)
				heredoc(g_shell->master->content->cmd[0]);
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
	if (status != g_shell->return_status)
		g_shell->return_status = WEXITSTATUS(status);
	dup2(g_shell->std_out, STDOUT_FILENO);
}
