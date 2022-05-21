/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 09:58:02 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/05/21 10:36:21 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/builtins.h"

void	ft_pwd(int fd)
{
	char	*p_dir;
	char	dir[PATH_MAX];

	p_dir = getcwd(dir, PATH_MAX);
	if (p_dir == NULL)
		perror("[ERROR]");
	write(fd, dir, ft_strlen(dir));
	write(fd, "\n", 1);
}
