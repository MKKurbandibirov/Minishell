/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:09:22 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/06 17:03:58 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/builtins.h"

int	cd_home(char *path, t_list *env, t_list *exp)
{
	char	*home;
	char	*t;

	home = getenv("HOME");
	if (!ft_strcmp(path, "") || !ft_strcmp(path, "~"))
	{
		if (chdir(home) != -1)
		{
			t = ft_strjoin("OLDPWD=", get_pwd(env, 1));
			ft_export(t, exp, env);
			free(t);
			t = ft_strjoin("PWD=", home);
			ft_export(t, exp, env);
			free(t);
		}
		else
			perror("[ERROR]");
		return (1);
	}
	return (0);
}

int	cd_relative_home(char *path, t_list *env, t_list *exp)
{
	char	*new_path;
	char	*home;
	char	*t;

	home = getenv("HOME");
	if (path[0] == '~')
	{
		new_path = ft_strjoin(home, ++path);
		if (chdir(new_path) != -1)
		{
			t = ft_strjoin("OLDPWD=", get_pwd(env, 1));
			ft_export(t, exp, env);
			free(t);
			t = ft_strjoin("PWD=", new_path);
			ft_export(t, exp, env);
			free(t);
		}
		else
			perror("[ERROR]");
		free(new_path);
		return (1);
	}
	return (0);
}

int	cd_double_dot(char *path, t_list *env, t_list *exp)
{
	char	*tmp;
	char	*tail;
	char	*t;

	if (!ft_strcmp(path, ".."))
	{
		tmp = ft_strdup(get_pwd(env, 1));
		tail = ft_strrchr(tmp, '/');
		tmp[tail - tmp] = '\0';
		if (chdir(tmp) != -1)
		{
			t = ft_strjoin("OLDPWD=", get_pwd(env, 1));
			ft_export(t, exp, env);
			free(t);
			t = ft_strjoin("PWD=", tmp);
			ft_export(t, exp, env);
			free(t);
		}
		else
			perror("[ERROR]");
		free(tmp);
		return (1);
	}
	return (0);
}

int	cd_dot(char *path, t_list *env, t_list *exp)
{
	char	*tmp;
	char	*t;

	if (!ft_strcmp(path, "."))
	{
		tmp = get_pwd(env, 1);
		if (chdir(tmp) != 1)
		{
			t = ft_strjoin("OLDPWD=", tmp);
			ft_export(t, exp, env);
			free(t);
			t = ft_strjoin("PWD=", tmp);
			ft_export(t, exp, env);
			free(t);
		}
		else
			perror("[ERROR]");
		return (1);
	}
	return (0);
}

int	cd_minus(char *path, t_list *env, t_list *exp)
{
	char	*oldpwd;
	char	*pwd;
	char	*t;

	if (!ft_strcmp(path, "-"))
	{
		pwd = ft_strdup(get_pwd(env, 1));
		oldpwd = ft_strdup(get_pwd(env, 2));
		printf("%s\n", oldpwd);
		if (chdir(oldpwd) != -1)
		{
			t = ft_strjoin("OLDPWD=", pwd);
			ft_export(t, exp, env);
			free(t);
			t = ft_strjoin("PWD=", oldpwd);
			ft_export(t, exp, env);
			free(t);
			free(pwd);
			free(oldpwd);
		}
		else
			perror("[ERROR]");
		return (1);
	}
	return (0);
}
