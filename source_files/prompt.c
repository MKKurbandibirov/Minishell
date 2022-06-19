/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 09:05:14 by magomed           #+#    #+#             */
/*   Updated: 2022/06/11 14:49:01 by nfarfetc         ###   ########.fr       */
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
		prompt = ft_strjoin(pwd[i], ":> ");
		free_split(pwd);
		return (prompt);
	}
	return (NULL);
}
