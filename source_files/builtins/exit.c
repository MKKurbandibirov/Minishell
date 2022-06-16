/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 09:21:18 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/16 18:02:06 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/builtins.h"

void	ft_exit(int return_stat)
{
	g_shell->return_status = return_stat;
	free_split(g_shell->cmd_path);
	free_list(g_shell->env);
	free_list(g_shell->exp);
	free(g_shell->prompt);
	clear_history();
	exit(return_stat);
}
