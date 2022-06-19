/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:10:54 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/16 15:48:34 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/parser.h"

void	ft_err_msg(char *msg)
{
	write(2, msg, ft_strlen(msg));
}

char	*ft_srch_pair_quote(char *s, int c)
{
	int	i;
	int	f_i;

	i = 0;
	f_i = -1;
	while (s[i] != 0)
	{
		if (s[i] == c && s[i - 1] != '\\')
		{
			f_i = i;
			break ;
		}
		i++;
	}
	if (c == '\0')
		return (&s[i]);
	else if (f_i == -1)
		return (NULL);
	else
		return (&s[f_i]);
}

char	*ft_env_search(char *dollar)
{
	t_list	*curr;

	curr = g_shell->env;
	while (curr != NULL)
	{
		if (!ft_strcmp(((t_key_val *)curr->content)->key, dollar))
			break ;
		curr = curr->next;
	}
	if (!curr)
		return (NULL);
	return (((t_key_val *)curr->content)->val);
}

char	*ft_ifdollar(char *s, int *len)
{
	char	*dollar;
	char	*ret;

	*len = 0;
	while (s[*len] && (ft_isalpha(s[*len]) || ft_isdigit(s[*len]))
		&& (!ft_isspace(s[*len])))
		(*len)++;
	dollar = (char *) malloc(sizeof(char) * (*len) + 1);
	ft_strncpy(s, dollar, *(len) + 1);
	(*len)--;
	ret = ft_strdup(ft_env_search(dollar));
	free(dollar);
	return (ret);
}

int	ft_isspec(char c)
{
	if (c == '|' || c == '&' || c == '<' || c == '>')
		return (1);
	return (0);
}
