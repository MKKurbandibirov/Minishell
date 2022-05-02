/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 14:52:08 by nfarfetc          #+#    #+#             */
/*   Updated: 2021/10/10 15:00:53 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;
	int		len;
	int		i;

	i = 0;
	len = 0;
	temp = lst;
	while (temp != NULL)
	{
		len++;
		temp = temp->next;
	}
	while (i < len - 1)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}
