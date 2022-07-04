/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 09:37:32 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:06:38 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_c;
	unsigned char	*src_c;

	dst_c = (unsigned char *)dst;
	src_c = (unsigned char *)src;
	if (src_c < dst_c)
	{
		while (len > 0)
		{
			*(dst_c + (len - 1)) = *(src_c + (len - 1));
			len--;
		}
	}
	else if (src_c > dst_c)
	{
		while (len > 0)
		{
			*dst_c++ = *src_c++;
			len--;
		}
	}
	return (dst);
}
