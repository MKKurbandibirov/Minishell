/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:23:45 by gtaggana          #+#    #+#             */
/*   Updated: 2022/07/04 17:08:43 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/parser.h"

static char	*ft_dbl_quotes_subsit(char *s)
{
	int		pt;
	int		add_len;
	char	*dlr;
	char	*ret;

	pt = -1;
	ret = ft_substr("", 0, 1);
	while (s[++pt])
	{
		if (s[pt] == '$' && s[pt + 1]
			&& (ft_isalpha(s[pt + 1]) || ft_isdigit(s[pt + 1])))
		{
			dlr = ft_ifdollar(&s[++pt], &add_len);
			pt += (add_len - 1);
			if (!dlr)
				continue ;
			ret = ft_strjoin_free(ret, dlr, 3);
		}
		else
			ret = ft_strjoin_c_free(ret, s[pt]);
	}
	return (ret);
}

static char	*ft_dbl_replacement(char *s)
{
	int		pt;
	int		new_len;
	char	*new;

	pt = -1;
	new_len = 0;
	while (s[++pt])
	{
		if (s[pt] != '\\' && s[pt + 1] && s[pt + 1] != '\"')
			new_len++;
	}
	new = (char *)malloc(sizeof(char) * new_len + 1);
	pt = -1;
	new_len = 0;
	while (s[++pt])
	{
		if (s[pt] == '\\' && s[pt + 1] && s[pt + 1] == '\"')
			continue ;
		new[new_len++] = s[pt];
	}
	new[new_len] = '\0';
	free(s);
	return (new);
}

char	*ft_dbl_quote(char *s)
{
	char	*next_c;
	char	*ret;
	int		len;

	next_c = ft_srch_pair_quote(&s[1], s[0]);
	len = next_c - &s[0];
	ret = malloc(len + 1);
	ft_strncpy(&s[1], ret, len);
	ret = ft_dbl_replacement(ret);
	ret = ft_dbl_quotes_subsit(ret);
	return (ret);
}

char	*ft_single_quote(char *s)
{
	char	*ret;
	int		len;

	len = ft_strchr(&s[1], s[0]) - &s[0];
	ret = malloc(len + 1);
	ft_strncpy(&s[1], ret, len);
	return (ret);
}
