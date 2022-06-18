/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:49:55 by magomed           #+#    #+#             */
/*   Updated: 2022/06/18 12:13:51 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/minishell.h"
// #include "../header_files/parser.h"

// char	***create_example(void)
// {
// 	char	***ex;
// 	ex = malloc(sizeof(char **) * 4);
// 	ex[0] = ft_split("/bin/ls", ' ');
// 	ex[1] = ft_split("/usr/bin/grep *.c", ' ');
// 	ex[2] = ft_split("/usr/bin/wc -l", ' ');
// 	ex[3] = NULL;
// 	return ex;
// }

char	*change_shlvl(void)
{
	t_list	*curr;
	int		lvl;
	char	*new;

	curr = g_shell->env;
	while (curr != NULL)
	{
		if (!ft_strcmp("SHLVL", ((t_key_val *)curr->content)->key))
			lvl = ft_atoi(((t_key_val *)curr->content)->val);
		curr = curr->next;
	}
	new = ft_strjoin_free("SHLVL=", ft_itoa(lvl + 1), 2);
	return (new);
}

t_minishell	*init_shell(int argc, char **argv, char **envr)
{
	char	*shlvl;

	(void)argc;
	(void)argv;
	g_shell = (t_minishell *)malloc(sizeof(t_minishell));
	if (!g_shell)
		return (NULL);
	g_shell->env = get_envr(envr);
	g_shell->exp = get_expt(envr);
	g_shell->pids = NULL;
	g_shell->status = NULL;
	g_shell->return_status = 0;
	g_shell->pwd = NULL;
	g_shell->prompt = NULL;
	shlvl = change_shlvl();
	ft_export(shlvl, g_shell->exp, g_shell->env);
	free(shlvl);
	path_parse();
	return (g_shell);
}

int	main(int argc, char **argv, char **envr)
{
	char		*line;
	char		**cmd;

	init_shell(argc, argv, envr);
	main_sig();
	while (1)
	{
		g_shell->prompt = get_prompt();
		line = readline(g_shell->prompt);
		cmd = ft_split(line, ' ');
		if (!line || (!ft_strcmp("exit", cmd[0]) && cmd[1] == NULL))
			ft_exit(0);
		ft_parser_v2(line);
		ft_exe();
		add_history(line);
		free_split(cmd);
		free(g_shell->prompt);
		free(line);
	}
	clear_history();
	free_list(g_shell->env);
	free_list(g_shell->exp);
	free_split(g_shell->cmd_path);
	return (0);
}
