/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 10:13:31 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:03:35 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] != c && s[i + 1] && s[i + 1] == c)
			|| (s[i] != c && !s[i + 1]))
			count++;
		i++;
	}
	return (count);
}

static char	*allocate_word(char const *s, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

void	free_split(char **res)
{
	int	i;

	i = 0;
	if (res == NULL)
		return ;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
}

static char	**solver(char **result, char const *s, char c, int count)
{
	int	i;

	i = 0;
	while (i < count && *s)
	{
		if (*s && *s != c)
		{
			result[i] = allocate_word(s, c);
			if (!result[i])
			{
				free_split(result);
				return (NULL);
			}
			i++;
			while (*s && *s != c)
				s++;
		}
		s++;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		count;

	if (!s)
		return (NULL);
	count = count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	result = solver(result, s, c, count);
	return (result);
}
