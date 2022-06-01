/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:03:37 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/01 12:46:47 by nfarfetc         ###   ########.fr       */
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

	if (path[ft_strlen(path) - 1] == '/')
		path[ft_strlen(path) - 1] = '\0';
	tmp = get_pwd(env, 1);
	if (chdir(path) != -1)
	{
		ft_export(ft_strjoin_free("OLDPWD=", tmp, 3), exp, env, fd);
		tmp = ft_strjoin(tmp, "/");
		tmp = ft_strjoin_free(tmp, path, 1);
		ft_export(ft_strjoin_free("PWD=", tmp, 3), exp, env, fd);
		free(tmp);
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
