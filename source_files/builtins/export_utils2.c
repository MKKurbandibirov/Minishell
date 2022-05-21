/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:57:00 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/05/21 10:36:15 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/builtins.h"

int	key_validator(char *key)
{
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (key[i + 1])
	{
		if (key[i] == '\\' && key[i + 1] == '\\')
			return (-1);
		if (!ft_isascii(key[i]) && !ft_isdigit(key[i]))
			return (-1);
		if (key[i] == '\\')
			len--;
		i++;
		len++;
	}
	return (len);
}

char	*key_check(char *key)
{
	int		len;
	int		i;
	char	*new;

	len = key_validator(key);
	if (len == -1)
		return (NULL);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	i = -1;
	len = 0;
	while (key[++i])
	{
		if (key[i] != '\\')
		{
			new[len] = key[i];
			len++;
		}
	}
	free(key);
	key = new;
	return (new);
}
