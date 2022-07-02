/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_pars_here.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:22:58 by gtaggana          #+#    #+#             */
/*   Updated: 2022/07/02 12:00:22 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/execute.h"

char	*ft_here_dollar(char *s)
{
	int		i;
	char	*quote;
	char	*ret;

	i = 0;
	while (s[i] && !ft_isspace(s[i]) && s[i] != ')' && !ft_isspec(s[i]))
	{
		if (s[i] == '\"')
			quote = ft_dbl_quote(&s[i]);
		else if (s[i] == '\'')
			quote = ft_single_quote(&s[i]);
		if (s[i] == '\"' || s[i] == '\'')
		{
			i += ft_skip_quote(&s[i]) + 1;
			ret = ft_strjoin_free(ret, quote, 3);
		}
		else
			ret = ft_strjoin_c_free(ret, s[i++]);
	}
	return (ret);
}
