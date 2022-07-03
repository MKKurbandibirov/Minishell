/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 09:21:18 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/03 10:38:06 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/builtins.h"

void	ft_exit(int return_stat, int opt)
{
	g_shell->ret_stat = return_stat;
	free_global();
	free_inter(NULL);
	if (opt)
		printf("%s\n", "exit");
	exit(return_stat);
}

void	free_global(void)
{
	free_split(g_shell->cmd_path);
	free_list(g_shell->env);
	free_list(g_shell->exp);
	free(g_shell->master);
	free(g_shell->pwd);
	free(g_shell);
	clear_history();
}

void	free_inter(char *line)
{
	if (line != NULL)
		free(line);
	// free_simple_list(g_shell->pids);
	free(g_shell->prompt);
}
