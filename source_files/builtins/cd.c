/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:03:37 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:07:59 by nfarfetc         ###   ########.fr       */
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

int	cd_path(char *path, t_list *env, t_list *exp)
{
	char	*tmp;
	char	*t;

	tmp = g_shell->pwd;
	if (chdir(path) != -1)
	{
		if (path[ft_strlen(path) - 1] == '/')
			path[ft_strlen(path) - 1] = '\0';
		t = ft_strjoin("OLDPWD=", tmp);
		ft_export(t, exp, env);
		free(t);
		tmp = ft_strjoin(tmp, "/");
		tmp = ft_strjoin_free(tmp, path, 1);
		t = ft_strjoin("PWD=", tmp);
		ft_export(t, exp, env);
		free(tmp);
		free(t);
		return (1);
	}
	perror("[ERROR]");
	return (0);
}

static char	*helper(char *tmp, char *path)
{
	char	*tail;
	char	*t;

	tail = ft_strrchr(tmp, '/');
	tmp[tail - tmp] = '\0';
	tmp = ft_strjoin_free(tmp, path + 2, 1);
	t = ft_strjoin("PWD=", tmp);
	free(tmp);
	return (t);
}

int	cd_relative_path(char *path, t_list *env, t_list *exp)
{
	char	*tmp;
	char	*t;

	if (path[0] == '.' && path[1] == '.')
	{
		if (path[ft_strlen(path) - 1] == '/')
			path[ft_strlen(path) - 1] = '\0';
		tmp = ft_strdup(g_shell->pwd);
		if (chdir(path) != -1)
		{
			t = ft_strjoin("OLDPWD=", tmp);
			ft_export(t, exp, env);
			free(t);
			t = helper(tmp, path);
			ft_export(t, exp, env);
			free(t);
			return (1);
		}
		perror("[ERROR]");
		return (0);
	}
	return (0);
}

void	ft_cd(char *path, t_list *env, t_list *exp)
{
	int			i;
	t_cd_util	cd_utils[6];

	cd_utils[0] = &cd_home;
	cd_utils[1] = &cd_relative_home;
	cd_utils[2] = &cd_dot;
	cd_utils[3] = &cd_double_dot;
	cd_utils[4] = &cd_relative_path;
	cd_utils[5] = &cd_path;
	i = 0;
	while (i < 6 && cd_utils[i](path, env, exp) != 1)
		i++;
}
