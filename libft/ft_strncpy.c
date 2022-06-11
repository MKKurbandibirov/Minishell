/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 14:47:30 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/11 14:47:35 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strncpy(char *src, char *direc, int len)
{
	char	*tmp;

	tmp = src;
	if (len)
	{
		while (len - 1 > 0 && *tmp)
		{
			*direc++ = *tmp++;
			len--;
		}
		*direc = '\0';
	}
}
