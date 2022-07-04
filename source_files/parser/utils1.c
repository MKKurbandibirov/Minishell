/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:24:14 by gtaggana          #+#    #+#             */
/*   Updated: 2022/07/04 17:08:53 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/parser.h"

char	*ft_check_scpec(char *s, int *add)
{
	*add = 2;
	if (!ft_strncmp(s, "<<", 2))
		return (ft_strdup("<<"));
	if (!ft_strncmp(s, ">>", 2))
		return (ft_strdup(">>"));
	if (!ft_strncmp(s, "||", 2))
		return (ft_strdup("||"));
	if (!ft_strncmp(s, "&&", 2))
		return (ft_strdup("&&"));
	*add = 1;
	if (!ft_strncmp(s, "<", 1))
		return (ft_strdup("<"));
	if (!ft_strncmp(s, ">", 1))
		return (ft_strdup(">"));
	if (!ft_strncmp(s, "&", 1))
		return (ft_strdup("&"));
	if (!ft_strncmp(s, "|", 1))
		return (ft_strdup("|"));
	return (NULL);
}

int	ft_check_type_first_arg(char *s, char c)
{
	if (c == '\'' || c == '\"')
		return (CMD);
	if (!ft_strncmp("<<", s, 2))
		return (HEREDOC);
	else if (!ft_strncmp(">>", s, 2))
		return (APPEND);
	else if (!ft_strncmp("<", s, 1))
		return (INFILE_RE);
	else if (!ft_strncmp(">", s, 1))
		return (OUTFILE_RE);
	if (ft_isspec(c))
		return (ERR);
	return (CMD);
}

int	ft_check_4_redir(char *s)
{
	if (!ft_strncmp("<<", s, 2))
		return (HEREDOC);
	else if (!ft_strncmp(">>", s, 2))
		return (APPEND);
	else if (!ft_strncmp("<", s, 1))
		return (INFILE_RE);
	else if (!ft_strncmp(">", s, 1))
		return (OUTFILE_RE);
	else
		return (ARG);
}

char	*ft_argv_am(char *s, int *add)
{
	int		i;
	char	*quote;
	char	*ret;

	i = 0;
	if (ft_isspec(s[i]))
		return (ft_check_scpec(&s[i], add));
	ret = ft_strdup("");
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
	*add = i;
	return (ret);
}

int	ft_checking_cause(char *s, int *grp, t_master *prs, int i)
{
	int	add;

	add = 0;
	if (s[i])
	{
		add++;
		if (s[i] == ')')
		{
			(*grp)++;
			i++;
			while (s[i] && ft_isspace(s[i]))
				i++;
		}
		else if (s[i] == '|' && (!s[i + 1] || s[i + 1] != '|'))
			ft_pushback_p(&prs->head, ft_strdup("|"), PIPE, *grp);
		else if (s[0] == '&' && (!s[i + 1] || s[i + 1] != '&'))
			ft_pushback_p(&prs->head, "&", BG, *grp);
		else if (s[i] == '|' || s[i] == '&')
		{
			(*grp)++;
			add++;
		}
		ft_checking_help(s, grp, prs, &i);
	}
	return (i + add);
}
