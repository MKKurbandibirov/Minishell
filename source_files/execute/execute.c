/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaggana <gtaggana@student.21-school       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:20:05 by gtaggana          #+#    #+#             */
/*   Updated: 2022/07/02 15:20:06 by gtaggana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/execute.h"

void	replace_status(char **content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (!ft_strcmp(content[i], "$?"))
		{
			free(content[i]);
			content[i] = ft_itoa(g_shell->ret_stat);
		}
		i++;
	}
}

void	exe_helper(void)
{
	int	fd;

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
	{
		fd = heredoc(g_shell->master->content->cmd[0]);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	exe_helper_wrap(void)
{
	while (g_shell->master->content != NULL)
	{
		exe_helper();
		ft_delelem_s(&g_shell->master->content,
			g_shell->master->content);
		g_shell->master->flag_del = 1;
	}
}

void	waiting(void)
{
	int	status;

	while (g_shell->pids)
	{
		status = g_shell->ret_stat;
		waitpid(*(int *)g_shell->pids->content, &status, 0);
		g_shell->pids = g_shell->pids->next;
	}
	if (status != g_shell->ret_stat)
		g_shell->ret_stat = WEXITSTATUS(status);
}

void	ft_exe(void)
{
	while (g_shell->master != NULL)
	{
		if (g_shell->master->t_connect == START)
			exe_helper_wrap();
		else if (g_shell->master->t_connect == AND && g_shell->ret_stat == 0)
			exe_helper_wrap();
		else if (g_shell->master->t_connect == ELSE && g_shell->ret_stat != 0)
			exe_helper_wrap();
		ft_delelem_m(&g_shell->master, g_shell->master);
		waiting();
		// dup2(g_shell->std_out, STDOUT_FILENO);
		free_simple_list(g_shell->pids);
	}
}
