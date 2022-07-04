/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:49:55 by magomed           #+#    #+#             */
/*   Updated: 2022/07/04 17:01:35 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/minishell.h"

t_minishell	*g_shell;

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
	g_shell->std_in = dup(STDIN_FILENO);
	g_shell->std_out = dup(STDOUT_FILENO);
	g_shell->env = get_envr(envr);
	g_shell->exp = get_expt(envr);
	g_shell->pids = NULL;
	g_shell->ret_stat = 0;
	g_shell->pwd = NULL;
	g_shell->prompt = NULL;
	shlvl = change_shlvl();
	ft_export(shlvl, g_shell->exp, g_shell->env);
	free(shlvl);
	return (g_shell);
}

int	main(int argc, char **argv, char **envr)
{
	char		*line;

	init_shell(argc, argv, envr);
	while (1)
	{
		main_sig();
		path_parse();
		g_shell->prompt = get_prompt();
		line = readline(g_shell->prompt);
		if (!line
			|| (!ft_parser_v2(line) && (g_shell->master->content
					&& (!ft_strcmp("exit", g_shell->master->content->cmd[0])
						&& g_shell->master->content->cmd[1] == NULL))))
			ft_exit(EXIT_SUCCESS, 1);
		ft_exe();
		add_history(line);
		free_inter(line);
	}
	return (0);
}
