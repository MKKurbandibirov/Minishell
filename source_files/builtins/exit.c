/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 09:21:18 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/21 10:59:26 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/builtins.h"

void	ft_exit(int return_stat)
{
	g_shell->return_status = return_stat;
	free_global();
	free_inter(NULL, NULL);
	exit(return_stat);
}

void	free_global(void)
{
	free_split(g_shell->cmd_path);
	free_list(g_shell->env);
	free_list(g_shell->exp);
	clear_history();
}

void	free_inter(char *line, char **cmd)
{
	if (line != NULL)
		free(line);
	if (cmd != NULL)
		free_split(cmd);
	free(g_shell->prompt);
}
