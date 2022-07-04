/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:23:38 by gtaggana          #+#    #+#             */
/*   Updated: 2022/07/04 17:08:38 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/parser.h"

int	ft_get_arg_continue(char *s, int *group, t_master *prs)
{
	int	add;

	add = 0;
	if (s[0] && s[0] == '<' && s[1] && s[1] == '<')
	{
		ft_pushback_p(&prs->head, ft_strdup("<<"), HEREDOC, *group);
		add += 2;
	}
	else if (s[0] && s[0] == '>' && s[1] && s[1] == '>')
	{
		ft_pushback_p(&prs->head, ft_strdup(">>"), APPEND, *group);
		add += 2;
	}
	else if (s[0] && s[0] == '>')
	{
		ft_pushback_p(&prs->head, ft_strdup(">"), OUTFILE_RE, *group);
		add++;
	}
	else if (s[0] && s[0] == '<')
	{
		ft_pushback_p(&prs->head, ft_strdup("<"), INFILE_RE, *group);
		add++;
	}
	return (add);
}

void	ft_get_flags_args(char *s, t_master *master, int *add, int *group)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '&' && s[i] != '|' && s[i] != ')')
	{
		*add = 0;
		if (s[i] && s[i] == '-')
			ft_pushback_p(&master->head, ft_argv_am(&s[i], add), FLAG, *group);
		else if (s[i] && !ft_isspec(s[i]))
			ft_pushback_p(&master->head, ft_argv_am(&s[i], add), ARG, *group);
		else
			i += ft_get_arg_continue(&s[i], group, master);
		i += (*add);
		while (s[i] && (ft_isspace(s[i]) || s[i] == '('))
			i++;
	}
	*add = i;
}

void	ft_get_redirect(char*s, t_master *master, int *add, int *group)
{
	int		i;
	int		type;
	t_plist	*last;

	i = 0;
	last = ft_getlast(master->head);
	while (s[i] && (ft_isspace(s[i]) || s[i] == '('))
			i++;
	while (s[i] && s[i] != '|'
		&& s[i] != ')' && s[i] != '&')
	{
		*add = 0;
		type = ft_check_4_redir(&s[i]);
		if (last->type == ARG && type == ARG)
			ft_pushback_p(&master->head, ft_argv_am(&s[i], add), CMD, *group);
		else
			ft_pushback_p(&master->head, ft_argv_am(&s[i], add), type, *group);
		last = ft_getlast(master->head);
		i += (*add);
		while (s[i] && (ft_isspace(s[i]) || s[i] == '('))
			i++;
	}
	*add = i;
}

int	ft_get_arg(char *s, int *group, t_master *prs, int i)
{
	int		add;
	t_plist	*last;

	last = ft_getlast(prs->head);
	while (s[i] && (ft_isspace(s[i]) || s[i] == '('))
		i++;
	while (s[i] && s[i] != '&' && s[i] != '|' && s[i] != ')')
	{
		add = 0;
		if (s[i] && last->type >= 6 && last->type <= 9)
			ft_get_redirect(&s[i], prs, &add, group);
		else if (s[i] && (last->type == 1 || last->type == 11
				|| last->type == 12))
			ft_get_flags_args(&s[i], prs, &add, group);
		i += add;
		while (s[i] && (ft_isspace(s[i]) || s[i] == '('))
			i++;
	}
	i += ft_checking_cause(&s[i], group, prs, 0);
	return (i);
}

void	ft_preparsing(t_master *master, char *s, int i, int add_len)
{
	int		group;
	char	*argument;

	group = 0;
	while (s[i])
	{
		while (ft_isspace(s[i]) || s[i] == '(')
			i++;
		if (s[i] && s[i] != ')')
		{
			argument = ft_argv_am(&s[i], &add_len);
			ft_pushback_p(&master->head, argument,
				ft_check_type_first_arg(argument, s[i]), group);
			i += (add_len);
		}
		if (s[i])
			i += (ft_get_arg(&s[i], &group, master, 0));
	}
}
