/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaggana <gtaggana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:18:28 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/06 17:01:56 by gtaggana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/parser.h"

t_parser	ft_pars_err_helper(t_parser *prs, int key_print)
{
	if (key_print == 1)
		printf("ERR NOT VALID STR!\n");
	ft_remove_list(prs);
	return (*prs);
}

int	ft_pars_helper(t_parser *prs, char *s1)
{
	ft_initparser(prs);
	return (ft_valid_first_arg(s1) + ft_validate_pairs(s1));
}

int	ft_count_cmd_word(t_plist *prs)
{
	int		i;
	t_plist	*curr;

	curr = prs;
	i = 0;
	if (curr->type == CMD)
	{
		while (curr && (curr->type == CMD
				|| curr->type == FLAG || curr->type == ARG))
		{
			i++;
			curr = curr->next;
		}
	}
	else
		i++;
	return (i);
}

char	**ft_get_cmd(t_parser *prs)
{
	char	**tmp;
	int		i;

	tmp = (char **) malloc(sizeof(char *) * (ft_count_cmd_word(prs->head) + 1));
	i = 0;
	while (prs->head && (prs->head->type == CMD
			|| prs->head->type == FLAG || prs->head->type == ARG))
	{
		tmp[i++] = ft_strdup(prs->head->data);
		ft_delelem(&prs->head, prs->head);
	}
	if (i == 0)
	{
		tmp[i++] = ft_strdup(prs->head->data);
		ft_delelem(&prs->head, prs->head);
	}
	tmp[i] = NULL;
	return (tmp);
}

t_parser	ft_pars(char *s1, int group, int add_len, int i)
{
	t_parser	prs;
	char		*s;

	if (ft_pars_helper(&prs, s1) != 0)
		return (ft_pars_err_helper(&prs, 1));
	s = ft_substitution(s1, 0);
	while (s[i])
	{
		while (ft_isspace(s[i]) || s[i] == '(')
			i++;
		if (s[i] && s[i] != ')')
		{
			ft_pushback_p(&prs.head, ft_argv_am(&s[i], &add_len), CMD, group);
			i += (add_len);
		}
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i])
			i += (ft_get_arg(&s[i], &group, &prs, 0));
	}
	ft_clear_parslst(&prs, s);
	if (ft_validator(prs.head))
		return (ft_pars_err_helper(&prs, 1));
	return (prs);
}
