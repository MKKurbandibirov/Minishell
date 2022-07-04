/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_pars_here.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:24:35 by gtaggana          #+#    #+#             */
/*   Updated: 2022/07/04 17:08:22 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/execute.h"

static char	*ft_norm_help(char *s, int *i)
{
	char	*tmp;
	int		add;
	char	*ret;

	add = 0;
	ret = ft_strdup("");
	*i += 1;
	tmp = ft_ifdollar(&s[1], &add);
	if (tmp != NULL)
		ret = ft_strjoin_free(ret, tmp, 3);
	else
	{
		free(tmp);
		free(ret);
		ret = NULL;
	}
	*i += add;
	return (ret);
}

static char	*ft_norm_help1(char *s)
{
	char	*ret;

	if (s[0] == '\"')
		ret = ft_dbl_quote(s);
	else if (s[0] == '\'')
		ret = ft_single_quote(s);
	return (ret);
}

char	*ft_here_dollar(char *s)
{
	int		i;
	char	*quote;
	char	*ret;

	i = 0;
	ret = ft_strdup("");
	while (s[i] && s[i] != ')' && !ft_isspec(s[i]))
	{
		quote = NULL;
		if (s[i] == '$')
			quote = ft_norm_help(&s[i], &i);
		if (s[i] == '\"' || s[i] == '\'')
		{
			quote = ft_norm_help1(&s[i]);
			i += ft_skip_quote(&s[i]) + 1;
			ret = ft_strjoin_free(ret, quote, 3);
		}
		else if (quote)
			ret = ft_strjoin_free(ret, quote, 3);
		else if (s[i] && s[i] != '$')
			ret = ft_strjoin_c_free(ret, s[i++]);
	}
	return (ret);
}
