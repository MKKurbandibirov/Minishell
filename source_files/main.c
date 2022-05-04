/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:49:55 by magomed           #+#    #+#             */
/*   Updated: 2022/05/04 13:57:24 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/minishell.h"

int	main(int argc, char **argv, char **envr)
{
	char	*line;
	char	**cmd;
	t_list	*my_env;
	t_list	*my_exp;

	my_env = get_envr(envr);
	my_exp = get_expt(envr);
	while (1)
	{
		line = readline("Assalamu_Aleykum:> ");
		cmd = ft_split(line, ' ');

		if (!ft_strcmp("echo", cmd[0]))
		{
			if (ft_echo_n(cmd, 0) == 1)
				printf("%s\n", "[WARR]: echo with no '-n' flag!");
		}
		else if (!ft_strcmp("pwd", cmd[0]))
		{
			if (cmd[1] == NULL)
				ft_pwd(0);
			else
				printf("%s\n", "[WARR]: pwd with flags!");
		}
		else if (!ft_strcmp("cd", cmd[0]))
		{
			if (cmd[1] == NULL)
				ft_cd("", 0);
			else
				ft_cd(cmd[1], 0);
		}
		else if (!ft_strcmp("env", cmd[0]))
		{
			if (cmd[1] == NULL)
				ft_env(my_env, 0);
			else
				printf("%s\n", "[WARR]: env with flags!");
		}
		else if (!ft_strcmp("export", cmd[0]))
		{
			if (ft_export(cmd, my_exp, my_env, 0))
				printf("%s\n", "[WARR]: export with flags!");
		}
		add_history(line);
	}
	clear_history();
	return (0);
}
