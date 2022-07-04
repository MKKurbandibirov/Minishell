/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:14:55 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:07:05 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	char	*res_c;

	if (!(s1 && s2))
		return (NULL);
	res = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	res_c = res;
	if (res)
	{
		while (*s1)
		{
			*res = *s1;
			res++;
			s1++;
		}
		while (*s2)
		{
			*res = *s2;
			res++;
			s2++;
		}
		*res = '\0';
		return (res_c);
	}
	return (NULL);
}
