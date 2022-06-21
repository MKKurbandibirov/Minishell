/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 10:21:55 by gtaggana          #+#    #+#             */
/*   Updated: 2022/06/20 15:21:10 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/parser.h"

void	ft_checking_help(char *s, int *grp, t_master *prs, int i)
{
	if (s[i] == '|' && s[i + 1] && s[i + 1] == '|')
		ft_pushback_p(&prs->head, ft_strdup("||"), ELSE, *grp);
	else if (s[i] == '&' && s[i + 1] && s[i + 1] == '&')
		ft_pushback_p(&prs->head, ft_strdup("&&"), AND, *grp);
}
