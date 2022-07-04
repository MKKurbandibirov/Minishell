/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:32:46 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:09:05 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/minishell.h"

void	handler(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \n", 3);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_shell->ret_stat = 1;
}

void	main_sig(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

void	inter_sig(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	child_sig(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
