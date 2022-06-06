/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaggana <gtaggana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:49:55 by magomed           #+#    #+#             */
/*   Updated: 2022/06/06 13:39:43 by gtaggana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/minishell.h"
#include "../header_files/parser.h"

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
	char		*line;
	char		**cmd;
	char		*prompt;
	t_parser	prs;

	(void)argc;
	(void)argv;
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
		prompt = get_prompt();
		line = readline(prompt);
		if (!line)
		{
			free_list(g_shell->env);
			free_list(g_shell->exp);
			free(prompt);
			free(line);
			clear_history();
			exit(EXIT_SUCCESS);
		}
		prs = ft_pars(line, 0, 0, 0);
		if (prs.head != NULL)
		{
			cmd = ft_get_cmd(&prs);
			if (builtin_parser(cmd, g_shell->env, g_shell->exp) == 0)
			{
				if (identify_cmd(cmd[0]))
				{
					solo_cmd_exec(cmd, 0, 0, NULL);
				}
				printf("\n\t\t\tkill\n");
				// ft_pipe(create_example(), 3, 0, 1);
			}
			add_history(line);
			free_split(cmd); // Why is this fucking function dont work
		}
		free(prompt);
		free(line);
	}
	clear_history();
	free_list(g_shell->env);
	free_list(g_shell->exp);
	return (0);
}
