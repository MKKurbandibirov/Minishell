/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:49:55 by magomed           #+#    #+#             */
/*   Updated: 2022/05/29 12:12:05 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/minishell.h"

char	***create_example(void)
{
	char	***ex;
	ex = malloc(sizeof(char **) * 4);
	ex[0] = ft_split("ls", ' ');
	ex[1] = ft_split("grep *.c", ' ');
	ex[2] = ft_split("wc -l", ' ');
	ex[3] = NULL;
	return ex;
}

int	main(int argc, char **argv, char **envr)
{
	(void)argc;
	(void)argv;
	char	*line;
	char	**cmd;

	g_shell = (t_minishell *)malloc(sizeof(t_minishell));
	if (!g_shell)
		return (1);
	g_shell->env = get_envr(envr);
	g_shell->exp = get_expt(envr);
	g_shell->return_status = 0;
	path_parse();
	main_sig();
	while (1)
	{
		line = readline(get_prompt());
		if (!line)
		{
			clear_history();
			free_list(g_shell->env);
			free_list(g_shell->exp);
			exit(EXIT_SUCCESS);
		}
		if (!ft_pars(line, 0, 0, 0))
		{
			cmd = ft_split(line, ' ');
			if (builtin_parser(cmd, g_shell->env, g_shell->exp) == 0)
			{
				if (identify_cmd(cmd[0]))
				{
					solo_cmd_exec(cmd, 0, 0, NULL);
				}
				// ft_pipe(create_example(), 3, 0, 1);
				
			}
			add_history(line);
			free_split(cmd);
			free(line);
		}
	}
	return (0);
}