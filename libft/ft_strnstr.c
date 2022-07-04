/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 10:33:02 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:07:21 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!n[0])
		return ((char *)h);
	while (i < len && h[i])
	{
		j = 0;
		while (i + j < len && h[i + j] == n[j])
		{
			j++;
		}
		if (!n[j])
			return ((char *)&h[i]);
		i++;
	}
	return (NULL);
}
