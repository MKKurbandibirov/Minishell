/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 09:21:18 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/21 12:49:15 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/builtins.h"

void	ft_exit(int return_stat)
{
	g_shell->return_status = return_stat;
	free_global();
	free_inter(NULL);
	exit(return_stat);
}

void	free_global(void)
{
	free_split(g_shell->cmd_path);
	free_list(g_shell->env);
	free_list(g_shell->exp);
	clear_history();
}

void	free_inter(char *line)
{
	if (line != NULL)
		free(line);
	free(g_shell->prompt);
}
