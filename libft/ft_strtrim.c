/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:10:28 by nfarfetc          #+#    #+#             */
/*   Updated: 2021/10/10 10:30:30 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_in_set(int c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		head;
	int		tail;
	char	*res;
	int		i;

	if (!(s1 && set))
		return (NULL);
	head = 0;
	while (s1[head] && char_in_set(s1[head], set))
		head++;
	tail = ft_strlen(s1) - 1;
	while (head < tail && char_in_set(s1[tail], set))
		tail--;
	res = malloc((tail - head + 2) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (head <= tail)
	{
		res[i] = s1[head];
		head++;
		i++;
	}
	res[i] = '\0';
	return (res);
}
