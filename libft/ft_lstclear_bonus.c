/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 10:05:12 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:06:16 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (lst && *lst)
	{
		while (*lst)
		{
			if ((*lst)->content)
				del((*lst)->content);
			tmp = *lst;
			*lst = tmp->next;
			free(tmp);
		}
		lst = NULL;
	}
}
