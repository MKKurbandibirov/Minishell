/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 15:08:12 by nfarfetc          #+#    #+#             */
/*   Updated: 2021/10/10 17:28:02 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	int		i;
	t_list	*last;

	i = 0;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	if (!(lst && new))
		return ;
	last = ft_lstlast(*lst);
	last->next = new;
}
