/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 09:41:03 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:07:09 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	const char	*tmp;

	tmp = src;
	if (dstsize != 0)
	{
		while (dstsize - 1 > 0 && *tmp)
		{
			*dst++ = *tmp++;
			dstsize--;
		}
		*dst = '\0';
	}
	return (ft_strlen(src));
}
