/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 09:37:44 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:07:08 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		len;
	size_t		result;

	len = ft_strlen(dst);
	if (dstsize < len)
		result = dstsize + ft_strlen(src);
	else
		result = len + ft_strlen(src);
	if (dstsize != 0)
	{
		while (len < dstsize - 1 && *src)
		{
			*(dst + len++) = *src++;
		}
		*(dst + len) = '\0';
	}
	return (result);
}
