/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 10:50:06 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:06:09 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	power(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	pow_10(int k)
{
	int	i;
	int	res;

	i = 0;
	res = 1;
	while (i < k)
	{
		res *= 10;
		i++;
	}
	return (res);
}

static void	solver(int i, int n, char *res)
{
	int	len;

	len = power(n);
	while (len > 0)
	{
		res[i] = '0' + (n / pow_10(len - 1)) % 10;
		len--;
		i++;
	}
	res[i] = '\0';
}

char	*ft_itoa(int n)
{
	char	*res;
	int		i;

	i = 0;
	if (n < 0)
	{
		if (n == -2147483648)
		{
			res = ft_strdup("-2147483648\0");
			return (res);
		}
		res = malloc((power(n) + 2) * sizeof(char));
		if (!res)
			return (NULL);
		res[0] = '-';
		i++;
		n *= -1;
	}
	else
		res = malloc((power(n) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	solver(i, n, res);
	return (res);
}
