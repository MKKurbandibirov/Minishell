/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 09:41:14 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:07:17 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && ((unsigned char)s1[i] || (unsigned char)s2[i]))
	{
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
		{
			return (1);
		}
		else if ((unsigned char)s1[i] < (unsigned char)s2[i])
		{
			return (-1);
		}
		i++;
	}
	return (0);
}
