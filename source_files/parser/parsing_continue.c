/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_continue.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:18:32 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/05/21 11:24:13 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/parser.h"

char	*ft_substitution(char *s, int pt)
{
	int		add_len;
	char	*test;
	char	*ret;

	ret = ft_substr("", 0, 1);
	while (s[++pt])
	{
		test = NULL;
		add_len = 1;
		if (s[pt] == '$' && s[pt + 1]
			&& (ft_isalpha(s[pt + 1]) || ft_isdigit(s[pt + 1])))
			test = ft_ifdollar(&s[++pt], &add_len);
		else if (s[pt] == '\'')
			test = ft_single_quote(&s[pt], &add_len);
		else if (s[pt] == '\"')
			test = ft_dbl_quoteproccessing(&s[pt], &add_len);
		else
			ret = ft_strjoin_c_free(ret, s[pt--]);
		if (test)
			ret = ft_strjoin_free(ret, test, 3);
		pt += (add_len);
	}
	return (ret);
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
	ret = ft_env_search(dollar);
	free(dollar);
	return (ret);
}
