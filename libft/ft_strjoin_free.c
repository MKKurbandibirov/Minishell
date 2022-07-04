/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:56:51 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:07:03 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	advanced_free(char *s1, char *s2, int option)
{
	if (option == 1)
		free(s1);
	else if (option == 2)
		free(s2);
	else
	{
		free(s1);
		free(s2);
	}
}

char	*ft_strjoin_free(char *s1, char *s2, int option)
{
	char	*new;
	int		i;
	int		j;

	if (!(s1 && s2))
		return (NULL);
	new = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
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
	advanced_free(s1, s2, option);
	return (new);
}

char	*ft_strjoin_c_free(char *s1, char s2)
{
	char	*new;
	int		i;

	if (!(s1 && s2))
		return (NULL);
	new = malloc((ft_strlen(s1) + 2) * sizeof(char));
	if (!new)
	{
		free(s1);
		return (NULL);
	}
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	new[i++] = s2;
	new[i] = '\0';
	free(s1);
	return (new);
}
