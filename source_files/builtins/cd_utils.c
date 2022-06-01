/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:09:22 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/01 12:50:24 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/builtins.h"

// Всё говно давай по новой(лики)

int	cd_home(char *path, t_list *env, t_list *exp, int fd)
{
	char	*home;

	home = getenv("HOME");
	if (!ft_strcmp(path, "") || !ft_strcmp(path, "~"))
	{
		if (chdir(home) != -1)
		{
			ft_export(ft_strjoin_free("OLDPWD=", get_pwd(env, 1), 3),
				exp, env, fd);
			ft_export(ft_strjoin_free("PWD=", home, 3), exp, env, fd);
		}
		else
			perror("[ERROR]");
		return (1);
	}
	return (0);
}

int	cd_relative_home(char *path, t_list *env, t_list *exp, int fd)
{
	char	*new_path;
	char	*home;

	home = getenv("HOME");
	if (path[0] == '~')
	{
		new_path = ft_strjoin(home, ++path);
		if (chdir(new_path) != -1)
		{
			ft_export(ft_strjoin_free("OLDPWD=", get_pwd(env, 1), 3),
				exp, env, fd);
			ft_export(ft_strjoin_free("PWD=", new_path, 3), exp, env, fd);
		}
		else
			perror("[ERROR]");
		free(new_path);
		return (1);
	}
	return (0);
}

int	cd_double_dot(char *path, t_list *env, t_list *exp, int fd)
{
	char	*tmp;
	char	*tail;

	if (!ft_strcmp(path, ".."))
	{
		tmp = ft_strdup(get_pwd(env, 1));
		tail = ft_strrchr(tmp, '/');
		tmp[tail - tmp] = '\0';
		if (chdir(tmp) != -1)
		{
			ft_export(ft_strjoin_free("OLDPWD=", get_pwd(env, 1), 3),
				exp, env, fd);
			ft_export(ft_strjoin_free("PWD=", tmp, 1), exp, env, fd);
		}
		else
			perror("[ERROR]");
		free(tmp);
		return (1);
	}
	return (0);
}

int	cd_dot(char *path, t_list *env, t_list *exp, int fd)
{
	char	*tmp;

	if (!ft_strcmp(path, "."))
	{
		tmp = get_pwd(env, 1);
		if (chdir(tmp) != 1)
		{
			ft_export(ft_strjoin_free("OLDPWD=", tmp, 3), exp, env, fd);
			ft_export(ft_strjoin_free("PWD=", tmp, 3), exp, env, fd);
		}
		else
			perror("[ERROR]");
		return (1);
	}
	return (0);
}

int	cd_minus(char *path, t_list *env, t_list *exp, int fd)
{
	char	*tmp;

	if (!ft_strcmp(path, "-"))
	{
		tmp = get_pwd(env, 2);
		if (chdir(tmp) != -1)
		{
			ft_export(ft_strjoin_free("OLDPWD=", get_pwd(env, 1), 3),
				exp, env, fd);
			ft_export(ft_strjoin_free("PWD=", tmp, 3), exp, env, fd);
		}
		else
			perror("[ERROR]");
		return (1);
	}
	return (0);
}
