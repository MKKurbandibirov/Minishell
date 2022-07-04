/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 14:47:30 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:07:19 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strncpy(char *src, char *direc, int len)
{
	int		i;
	char	*tmp;

	tmp = src;
	i = 0;
	if (len)
	{
		while (len - 1 > 0 && *tmp)
		{
			direc[i] = tmp[i];
			i++;
			len--;
		}
		direc[i] = '\0';
	}
}
