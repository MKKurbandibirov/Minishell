/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:03:37 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/05/06 16:50:51 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/builtins.h"

void	ft_cd(char *path, t_list *env, t_list *exp, int fd)
{
	char	*new_path;
	char	*pwd;
	char	*home;

	home = getenv("HOME");
	pwd = getenv("PWD");
	if (!ft_strcmp(path, "") || !ft_strcmp(path, "~"))
	{
		if (chdir(home) == -1)
			perror("[ERROR]");
		// printf("%s\n", ft_strjoin("OLDPWD=", pwd));
		ft_export(ft_strjoin("OLDPWD=", pwd), exp, env, fd);
		ft_export(ft_strjoin("PWD=", home), exp, env, fd);
	}
	else if (path[0] == '~')
	{
		home = ft_strjoin(home, "/");
		new_path = ft_strjoin(home, ++path);
		if (chdir(new_path) == -1)
			perror("[ERROR]");
		ft_export(ft_strjoin("OLDPWD=", pwd), exp, env, fd);
		ft_export(ft_strjoin("PWD=", new_path), exp, env, fd);
		free(new_path);
		free(home);
	}
	else
	{
		if (chdir(path) == -1)
			perror("[ERROR]");
		ft_export(ft_strjoin("OLDPWD=", pwd), exp, env, fd);
		ft_export(ft_strjoin("PWD=", path), exp, env, fd);
	}
}
