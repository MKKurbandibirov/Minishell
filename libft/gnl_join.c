/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:40:38 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:07:39 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*govnishe( char *str, int ch)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)ch)
			return ((char *)(str + i));
		i++;
	}
	if (str[i] == (char)ch)
		return ((char *)(str + i));
	return (NULL);
}

char	*checker(char *rem)
{
	if (!rem)
	{
		rem = malloc(sizeof(char));
		rem[0] = '\0';
	}
	return (rem);
}

char	*gnl_join(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	s1 = checker(s1);
	if (!(s1 && s2))
		return (NULL);
	new = malloc((ft_strlen(s1) + ft_strlen(s2) +1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		new[j++] = s1[i++];
	i = 0;
	while (s2[i])
		new[j++] = s2[i++];
	new[j] = '\0';
	free(s1);
	return (new);
}
