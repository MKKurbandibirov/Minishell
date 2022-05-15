/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:49:55 by magomed           #+#    #+#             */
/*   Updated: 2022/05/15 12:05:43 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/minishell.h"

int	norm_helper(char **cmd, t_list *env, t_list *exp)
{
	if (!ft_strcmp("env", cmd[0]) && cmd[1] == NULL)
	{
		ft_env(env, 0);
		return (1);
	}
	else if (!ft_strcmp("export", cmd[0]) && !ft_export(cmd[1], exp, env, 0))
		return (1);
	else if (!ft_strcmp("unset", cmd[0]) && !ft_unset(env, exp, cmd))
		return (1);
	else if (!ft_strcmp("exit", cmd[0]) && cmd[1] == NULL)
	{
		ft_exit();
		return (1);
	}
	return (0);
}

int	builtin_parser(char **cmd, t_list *env, t_list *exp)
{
	if (!ft_strcmp("echo", cmd[0]) && !ft_echo_n(cmd, 0))
		return (1);
	else if (!ft_strcmp("pwd", cmd[0]) && cmd[1] == NULL)
	{
		ft_pwd(0);
		return (1);
	}
	else if (!ft_strcmp("cd", cmd[0]))
	{
		if (cmd[1] == NULL)
			ft_cd("", env, exp, 0);
		else
			ft_cd(cmd[1], env, exp, 0);
		return (1);
	}
	else if (norm_helper(cmd, env, exp))
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **envr)
{
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
		line = readline("Assalamu_Aleykum:> ");
		if (!line)
			exit(EXIT_SUCCESS);
		cmd = ft_split(line, ' ');
		if (builtin_parser(cmd, g_shell->env, g_shell->exp) == 0)
		{
			if (identify_cmd(cmd[0]))
			{
				solo_cmd_exec(cmd, 0, 0);
			}
		}
		add_history(line);
		free_split(cmd);
	}
	clear_history();
	return (0);
}
