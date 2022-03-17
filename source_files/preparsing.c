/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:32:53 by magomed           #+#    #+#             */
/*   Updated: 2022/03/16 11:33:55 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/parser.h"

int	check_quotes(char *cmd)
{
	int	i;
	int	state;

	i = -1;
	state = STATE_GENERAL;
	while (cmd[++i])
	{
		if (cmd[i] == '\"' && state == STATE_GENERAL)
			state = STATE_IN_DQUOTE;
		else if (cmd[i] == '\'' && state == STATE_GENERAL)
			state = STATE_IN_QUOTE;
		else if (cmd[i] == '\"' && state == STATE_IN_DQUOTE)
			state = STATE_GENERAL;
		else if (cmd[i] == '\'' && state == STATE_IN_QUOTE)
			state = STATE_GENERAL;
	}
	if (state != STATE_GENERAL)
		return (1);
	return (0);
}

static int	ft_strlen(const char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		i++;
	}
	return (i);
}

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	if (!(s1 && s2))
		return (NULL);
	new = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!new)
	{
		free(s1);
		return (NULL);
	}
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

char	*enough_spaces(char *cmd)
{
	char	**tmp;
	char	*res;
	int		i;

	tmp = ft_split(cmd, ' ');
	res = malloc(sizeof(char));
	if (!res)
		return (NULL);
	res[0] = '\0';
	i = -1;
	while (tmp[++i])
	{
		res = ft_strjoin_free(res, tmp[i]);
		if (tmp[i + 1])
			res = ft_strjoin_free(res, " ");
	}
	free_split(tmp);
	return (res);
}
