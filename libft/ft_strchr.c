/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 09:36:08 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:06:53 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	int	i;
	int	f_i;

	i = 0;
	f_i = -1;
	while (s[i] != 0)
	{
		if (s[i] == c)
		{
			f_i = i;
			break ;
		}
		i++;
	}
	if (c == '\0')
		return (&s[i]);
	else if (f_i == -1)
		return (NULL);
	else
		return (&s[f_i]);
}
