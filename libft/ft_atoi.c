/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:18:27 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:05:44 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	spaces(const char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	long unsigned int	res;
	int					i;
	int					sign;

	i = 0;
	res = 0;
	sign = 1;
	i = spaces(str);
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
		if (res >= __LONG_MAX__ && sign == -1)
			return (0);
		if (res >= __LONG_MAX__ && sign == 1)
			return (-1);
	}
	return (res * sign);
}
