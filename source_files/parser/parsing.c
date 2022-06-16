// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   parsing.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: gtaggana <gtaggana@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/05/21 09:18:36 by nfarfetc          #+#    #+#             */
// /*   Updated: 2022/06/06 13:29:37 by gtaggana         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../header_files/parser.h"

// char	*ft_argv_am(char *s, int *add)
// {
// 	int		i;
// 	char	*ret;

// 	i = 0;
// 	while (s[i] && !ft_isspace(s[i]) && s[i] != '&'
// 		&& s[i] != '|' && s[i] != ')' && s[i] != '<'
// 		&& s[i] != '>')
// 		i++;
// 	*add = i;
// 	ret = (char *) malloc(sizeof(char) * i + 1);
// 	ft_strncpy(s, ret, i + 1);
// 	return (ret);
// }

// int	ft_checking_cause(char *s, int *grp, t_parser *prs)
// {
// 	int	add;

// 	add = 0;
// 	if (s[0])
// 	{
// 		add++;
// 		if (s[0] == ')')
// 			(*grp)++;
// 		else if (s[0] == '|' && (!s[1] || s[1] != '|'))
// 			ft_pushback_p(&prs->head, ft_strdup("|"), PIPE, *grp);
// 		else if (s[0] == '&' && (!s[1] || s[1] != '&'))
// 			ft_pushback_p(&prs->head, "&", BG, *grp);
// 		else
// 			add++;
// 		if (s[0] == '|' && s[1] && s[1] == '|')
// 			ft_pushback_p(&prs->head, ft_strdup("||"), OPER, *grp);
// 		else if (s[0] == '&' && s[1] && s[1] == '&')
// 			ft_pushback_p(&prs->head, ft_strdup("&&"), OPER, *grp);
// 	}
// 	return (add);
// }

// int	ft_get_arg_continue(char *s, int *group, t_parser *prs)
// {
// 	int	add;

// 	add = 0;
// 	if (s[0] && s[0] == '<' && s[1] && s[1] == '<')
// 	{
// 		ft_pushback_p(&prs->head, ft_strdup("<<"), HEREDOC, *group);
// 		add += 2;
// 	}
// 	else if (s[0] && s[0] == '>' && s[1] && s[1] == '>')
// 	{
// 		ft_pushback_p(&prs->head, ft_strdup(">>"), APPEND, *group);
// 		add += 2;
// 	}
// 	else if (s[0] && s[0] == '>')
// 	{
// 		ft_pushback_p(&prs->head, ft_strdup(">"), OUT, *group);
// 		add++;
// 	}
// 	else if (s[0] && s[0] == '<')
// 	{
// 		ft_pushback_p(&prs->head, ft_strdup("<"), IN, *group);
// 		add++;
// 	}
// 	return (add);
// }

// int	ft_get_arg(char *s, int *group, t_parser *prs, int i)
// {
// 	int	add;

// 	while (s[i] && s[i] != '&' && s[i] != '|' && s[i] != ')')
// 	{
// 		while (s[i] && (ft_isspace(s[i]) || s[i] == '('))
// 			i++;
// 		add = 0;
// 		if (s[i] && s[i] == '-')
// 			ft_pushback_p(&prs->head, ft_argv_am(&s[i], &add), FLAG, *group);
// 		else if (s[i] && s[i] == '\'')
// 			ft_pushback_p(&prs->head, ft_single_quote(&s[i], &add),
// 				ARG, *group);
// 		else if (s[i] && s[i] == '\"')
// 			ft_pushback_p(&prs->head, ft_dbl_quoteproccessing(&s[i], &add),
// 				ARG, *group);
// 		else
// 			add = ft_get_arg_continue(&s[i], group, prs);
// 		if (add == 0)
// 			ft_pushback_p(&prs->head, ft_argv_am(&s[i], &add), ARG, *group);
// 		i += add;
// 		while (s[i] && (ft_isspace(s[i]) || s[i] == '('))
// 			i++;
// 	}
// 	i += ft_checking_cause(&s[i], group, prs);
// 	return (i);
// }

// void	ft_clear_parslst(t_parser *prs, char *s)
// {
// 	t_plist	*curr;

// 	curr = prs->head;
// 	while (curr)
// 	{
// 		if (curr->data[0] == '\0')
// 			ft_delelem(&prs->head, curr);
// 		curr = curr->next;
// 	}
// 	free(s);
// }
