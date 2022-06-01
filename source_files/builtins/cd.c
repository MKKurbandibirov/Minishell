/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:03:37 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/01 14:04:24 by nfarfetc         ###   ########.fr       */
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

int	cd_path(char *path, t_list *env, t_list *exp, int fd)
{
	char	*tmp;
	char	*t;

	if (path[ft_strlen(path) - 1] == '/')
		path[ft_strlen(path) - 1] = '\0';
	tmp = get_pwd(env, 1);
	if (chdir(path) != -1)
	{
		t = ft_strjoin("OLDPWD=", tmp);
		ft_export(t, exp, env, fd);
		free(t);
		tmp = ft_strjoin(tmp, "/");
		tmp = ft_strjoin_free(tmp, path, 1);
		t = ft_strjoin("PWD=", tmp);
		ft_export(t, exp, env, fd);
		free(tmp);
		free(t);
	}
	else
		perror("[ERROR]");
	return (1);
}

void	ft_cd(char *path, t_list *env, t_list *exp, int fd)
{
	int			i;
	t_cd_util	cd_utils[6];

	cd_utils[0] = &cd_home;
	cd_utils[1] = &cd_relative_home;
	cd_utils[2] = &cd_dot;
	cd_utils[3] = &cd_double_dot;
	cd_utils[4] = &cd_minus;
	cd_utils[5] = &cd_path;
	i = 0;
	while (cd_utils[i](path, env, exp, fd) != 1)
		i++;
}
