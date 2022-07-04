/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:01:19 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:06:49 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	num;

	num = '0';
	if (n < 0)
	{
		write(fd, &"-", 1);
	}
	if (n <= 9 && n >= -9)
	{
		num = '0' + _abs(n);
		write(fd, &num, 1);
	}
	else
	{
		ft_putnbr_fd(_abs(n / 10), fd);
		ft_putnbr_fd(_abs(n % 10), fd);
	}
}
