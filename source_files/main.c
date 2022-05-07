/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:49:55 by magomed           #+#    #+#             */
/*   Updated: 2022/05/07 13:17:59 by nfarfetc         ###   ########.fr       */
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

// void	handler(int sig)
// {
// 	(void)sig;
// 	rl_on_new_line();
// 	rl_redisplay();
// 	write(1, "  \n", 3);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }

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
		builtin_parser(cmd, my_env, my_exp);
		add_history(line);
		free_split(cmd);
		// signal(SIGINT, handler);		
	}
	clear_history();
	return (0);
}
