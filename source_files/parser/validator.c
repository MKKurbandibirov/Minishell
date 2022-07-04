/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:22:05 by gtaggana          #+#    #+#             */
/*   Updated: 2022/07/04 17:09:01 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/parser.h"

static void	ft_first(t_plist *prs, int *status)
{
	t_plist	*curr;

	curr = prs;
	while (curr)
	{
		if ((curr->type == ERR) || ((curr->type > 3 && curr->type < 13)
				&& curr->next
				&& (curr->next->type > 3 && curr->next->type < 13))
			|| (curr->type > 3 && curr->type < 13 && curr->next == NULL))
		{
			*status = 1;
			return ;
		}
		curr = curr->next;
	}
}

int	ft_validator(t_plist *prs)
{
	int	status;

	status = 0;
	ft_first(prs, &status);
	if (status != 0)
	{
		while (prs)
			ft_delelem(&prs, prs);
		printf("Errrrr: Something is wrong with the token\n");
		return (1);
	}
	return (0);
}
