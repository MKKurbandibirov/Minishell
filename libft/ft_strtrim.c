/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:10:28 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/05/21 10:49:19 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_in_set(int c, char *set)
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

int	find_head(char *s1, char *set)
{
	int	head;

	head = 0;
	while (s1[head] && char_in_set(s1[head], set))
		head++;
	return (head);
}

char	*ft_strtrim(char *s1, char *set)
{
	int		head;
	int		tail;
	char	*res;
	int		i;

	if (!(s1 && set))
		return (NULL);
	head = find_head(s1, set);
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
	free(s1);
	return (res);
}

// char *ft_strtrim(char  *s1, char const *set)
// {
//  size_t size;

//  if (!s1)
//   return (NULL);
//  while (*s1 && ft_strchr(set, *s1))
//   s1++;
//  size = ft_strlen(s1);
//  while (size && ft_strchr(set, s1[size]))
//   size--;
//  return (ft_substr(s1, 0, size + 1));
// }
