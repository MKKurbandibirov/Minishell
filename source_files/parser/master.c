/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:38:17 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/16 15:40:59 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/parser.h"

t_master	*ft_getlast_m(t_master *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	ft_pushback_m(t_master **master, int type_c, int type)
{
	t_master	*tmp;
	t_master	*last;

	last = ft_getlast_m(*master);
	tmp = (t_master *) malloc(sizeof(t_master));
	if (!tmp)
	{
		perror("Err malloc (PB)");
		exit(EXIT_FAILURE);
	}
	tmp->head = (*master)->head;
	tmp->groupe = (*master)->head->group;
	tmp->content = ft_generate_cont(&(tmp->head), &type);
	tmp->next = NULL;
	if (!last)
	{
		(*master)->type_connect = START;
		(*master) = tmp;
		(*master)->prev = NULL;
	}
	else
	{
		(*master)->type_connect = type_c;
		last->next = tmp;
		tmp->prev = last;
	}
}
