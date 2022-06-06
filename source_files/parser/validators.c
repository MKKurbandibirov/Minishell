/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:19:52 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/05/21 11:24:24 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/parser.h"

int	ft_validate_pairs(char *s)
{
	int		i;
	int		status;
	char	last_c;

	i = -1;
	status = 0;
	last_c = s[0];
	while (s[++i])
	{
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
	}
	return (status);
}

int	ft_valid_first_arg(char *s)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (s[i] && (ft_isspace(s[i]) || s[i] == '('))
		i++;
	if (s[i] && (s[i] == '|' || s[i] == '&'))
		status = 1;
	return (status);
}

int	ft_validator(t_plist *curr)
{
	while (curr && curr->type == CMD)
	{
		curr = curr->next;
		while (curr != NULL && (curr->type == FLAG || curr->type == ARG))
			curr = curr->next;
		if (curr != NULL && (curr->type == OUT || curr->type == APPEND))
		{
			curr = curr->next;
			if (curr->type == ARG)
				curr = curr->next;
			else
				return (EXIT_FAILURE);
		}
		if (curr != NULL && (curr->type == PIPE
				|| curr->type == OPER || curr->type == BG))
			curr = curr->next;
	}
	// TODO << >> < >
	if (curr == NULL)
		return (0);
	return (EXIT_FAILURE);
}
