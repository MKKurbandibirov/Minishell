/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 10:05:12 by nfarfetc          #+#    #+#             */
/*   Updated: 2021/10/10 17:30:08 by nfarfetc         ###   ########.fr       */
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
