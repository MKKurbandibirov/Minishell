/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:49:55 by magomed           #+#    #+#             */
/*   Updated: 2022/05/03 13:25:35 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/minishell.h"

t_list	*get_envr(char **envr)
{
	int		i;
	int		j;
	t_env	*env;
	t_list	*env_list;
	t_list	*tmp;

	env_list = (t_list *)malloc(sizeof(t_list));
	i = 0;
	env_list = NULL;
	while (envr[i])
	{
		j = 0;
		while (envr[i][j] != '=')
			j++;
		env = (t_env *)malloc(sizeof(t_env));
		env->key = ft_substr(envr[i], 0, j);
		env->value = ft_substr(envr[i], j + 1, ft_strlen(envr[i]) - j);
		tmp = ft_lstnew(env);
		ft_lstadd_back(&env_list, tmp);
		i++;
	}
	return (env_list);
}

void	listsort(t_list *list)
{
	
}

t_list	*get_expt(char **envr)
{
	int		i;
	t_list	*exp_list;
	t_list	*tmp;

	i = 0;
	exp_list = (t_list *)malloc(sizeof(t_list));
	exp_list = NULL;
	while (envr[i])
	{
		if (envr[i][0] != '_' && envr[1] != '=')
		{
			tmp = ft_lstnew(ft_strdup(envr[i]));
			ft_lstadd_back(&exp_list, tmp);
		}
		i++;
	}
	return (exp_list);
}

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
		// else if (!ft_strcmp("export", cmd[0]))
		// {
		// 	if (cmd[1] == NULL)
		// 		ft_export(my_exp, 0);
		// 	else
		// 		printf("%s\n", "[WARR]: export with flags!");
		// }
		add_history(line);
	}
	clear_history();
	return (0);
}
