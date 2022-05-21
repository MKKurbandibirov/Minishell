/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:03:37 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/05/21 10:35:50 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/builtins.h"

char	*get_pwd(t_list *env, int opt)
{
	t_list	*curr;

	curr = env;
	while (curr != NULL)
	{
		if (!ft_strcmp(((t_key_val *)curr->content)->key, "PWD") && opt == 1)
			return (((t_key_val *)curr->content)->val);
		if (!ft_strcmp(((t_key_val *)curr->content)->key, "OLDPWD") && opt == 2)
			return (((t_key_val *)curr->content)->val);
		curr = curr->next;
	}
	return (NULL);
}

int	norm_helper1(char *path, t_list *env, t_list *exp, int fd)
{
	char	*new_path;
	char	*home;

	home = getenv("HOME");
	if (!ft_strcmp(path, "") || !ft_strcmp(path, "~"))
	{
		if (chdir(home) == -1)
			perror("[ERROR]");
		ft_export(ft_strjoin("OLDPWD=", get_pwd(env, 1)), exp, env, fd);
		ft_export(ft_strjoin("PWD=", home), exp, env, fd);
		return (1);
	}
	else if (path[0] == '~')
	{
		new_path = ft_strjoin(home, ++path);
		if (chdir(new_path) == -1)
			perror("[ERROR]");
		ft_export(ft_strjoin("OLDPWD=", get_pwd(env, 1)), exp, env, fd);
		ft_export(ft_strjoin("PWD=", new_path), exp, env, fd);
		free(new_path);
		return (1);
	}
	return (0);
}

int	norm_helper2(char *path, t_list *env, t_list *exp, int fd)
{
	char	*tmp;

	if (!ft_strcmp(path, "-"))
	{
		tmp = get_pwd(env, 2);
		if (chdir(get_pwd(env, 2)) == -1)
			perror("[ERROR]");
		ft_export(ft_strjoin("OLDPWD=", get_pwd(env, 1)), exp, env, fd);
		ft_export(ft_strjoin("PWD=", tmp), exp, env, fd);
		return (1);
	}
	else
	{
		if (chdir(path) == -1)
			perror("[ERROR]");
		ft_export(ft_strjoin("OLDPWD=", get_pwd(env, 1)), exp, env, fd);
		ft_export(ft_strjoin("PWD=", path), exp, env, fd);
		return (1);
	}
	return (0);
}

void	ft_cd(char *path, t_list *env, t_list *exp, int fd)
{
	if (!norm_helper1(path, env, exp, fd))
		norm_helper2(path, env, exp, fd);
}
