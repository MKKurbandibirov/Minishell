/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaggana <gtaggana@student.21-school       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:24:18 by gtaggana          #+#    #+#             */
/*   Updated: 2022/07/02 15:24:19 by gtaggana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/parser.h"

void	ft_checking_help(char *s, int *grp, t_master *prs, int *i)
{
	if (s[*i] == '|' && s[*i + 1] && s[*i + 1] == '|')
	{
		ft_pushback_p(&prs->head, ft_strdup("||"), ELSE, *grp);
		*i += 1;
	}
	else if (s[*i] == '&' && s[*i + 1] && s[*i + 1] == '&')
	{
		ft_pushback_p(&prs->head, ft_strdup("&&"), AND, *grp);
		*i += 1;
	}
}
