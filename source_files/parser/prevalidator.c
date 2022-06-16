/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prevalidator_v2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:09:54 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/16 11:19:35 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/parser.h"

int	ft_skip_quote(char *s)
{
	char	*next_c;

	if (s[0] == '\"')
		next_c = ft_srch_pair_quote(&s[1], '\"');
	else
		next_c = ft_strchr(&s[1], '\'');
	return (next_c - &s[0]);
}

static int	ft_valid_pairs_bracket(char *s)
{
	int		i;
	int		status;
	char	last_c;

	i = 0;
	status = 0;
	last_c = s[0];
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			i += ft_skip_quote(&s[i]);
		if (s[i] == '(' && last_c != ')')
			status++;
		else if (s[i] == ')' && status > 0 && last_c != '(')
			status--;
		else if ((s[i] == ')' && status == 0)
			|| (s[i] == '(' && last_c == ')')
			|| (s[i] == ')' && last_c == '('))
			return (1);
		if (!ft_isspace(s[i]))
			last_c = s[i];
		i++;
	}
	return (status);
}

static int	ft_chk_qt_prs(char *s)
{
	int		i;
	char	*next_c;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			if (s[i] == '\"')
				next_c = ft_srch_pair_quote(&s[++i], '\"');
			else
				next_c = ft_strchr(&s[++i], '\'');
			if (next_c == NULL)
				return (1);
			i += next_c - &s[i];
		}
		i++;
	}
	return (0);
}

int	ft_prevalidation(char *s)
{
	int	status;

	status = ft_chk_qt_prs(s);
	if (status != 0)
		ft_err_msg("Errr: Something with quotes\n");
	status = ft_valid_pairs_bracket(s);
	if (status != 0)
		ft_err_msg("Errr: Something with brackets\n");
	return (status);
}
