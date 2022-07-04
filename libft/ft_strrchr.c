/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 09:41:18 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:07:22 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *s, int c)
{
	int	i;
	int	max_i;

	i = 0;
	max_i = -1;
	while (s[i] != 0)
	{
		if (s[i] == c && i >= max_i)
		{
			max_i = i;
		}
		i++;
	}
	if (c == '\0')
		return (&s[i]);
	else if (max_i == -1)
		return (NULL);
	else
		return (&s[max_i]);
}
