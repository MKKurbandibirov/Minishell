/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 09:05:14 by magomed           #+#    #+#             */
/*   Updated: 2022/07/04 17:09:03 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/minishell.h"

void	save_pwd(void)
{
	char	*pwd;

	pwd = get_pwd(g_shell->env, 1);
	if (pwd)
	{
		if (g_shell->pwd)
			free(g_shell->pwd);
		g_shell->pwd = ft_strdup(pwd);
		return ;
	}
}

char	*get_prompt(void)
{
	int		i;
	char	*prompt;
	char	**pwd;

	save_pwd();
	pwd = ft_split(g_shell->pwd, '/');
	if (pwd)
	{
		i = 0;
		while (pwd[i + 1])
			i++;
		prompt = ft_strjoin("\x1b[32m", pwd[i]);
		prompt = ft_strjoin_free(prompt, "\x1b[31m", 1);
		prompt = ft_strjoin_free(prompt, ":> ", 1);
		prompt = ft_strjoin_free(prompt, "\x1b[0m", 1);
		free_split(pwd);
		return (prompt);
	}
	return (NULL);
}
