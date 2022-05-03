/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:03:37 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/05/03 10:22:14 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/builtins.h"

void	ft_cd(char *path, int fd)
{
	char	*new_path;
	char	*home;

	if (!ft_strcmp(path, "") || !ft_strcmp(path, "~"))
	{
		home = getenv("HOME");
		if (chdir(home) == -1)
			perror("[ERROR]");
	}
	else if (path[0] == '~')
	{
		home = getenv("HOME");
		home = ft_strjoin(home, "/");
		new_path = ft_strjoin(home, ++path);
		if (chdir(new_path) == -1)
			perror("[ERROR]");
		free(new_path);
		free(home);
	}
	else if (chdir(path) == -1)
	{
		perror("[ERROR]");
	}
}
