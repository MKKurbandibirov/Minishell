/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_n.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:19:21 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/05/21 10:50:35 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/builtins.h"

static int	has_flag(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '-')
		return (0);
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	return (1);
}

int	ft_echo_n(char **cmd, int fd)
{
	int	i;

	i = 1;
	while (cmd[i] && has_flag(cmd[i]))
		i++;
	if (i != 1)
	{
		while (cmd[i])
		{
			write(fd, cmd[i], ft_strlen(cmd[i]));
			if (cmd[i + 1] != NULL)
				write(fd, " ", 1);
			i++;
		}
		return (0);
	}
	return (1);
}
