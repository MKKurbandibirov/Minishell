/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:22:01 by gtaggana          #+#    #+#             */
/*   Updated: 2022/07/04 17:08:30 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/parser.h"

t_master	*ft_getlast_m(t_master *head)
{
	if (head->next == NULL && head->content == NULL)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	ft_delelem_m(t_master **head, t_master *delElem)
{
	if (*head == NULL || ((*head)->content == NULL && (*head)->flag_del == 0)
		|| delElem == NULL)
	{
		*head = NULL;
		return ;
	}
	if (*head == delElem)
		*head = delElem->next;
	if (delElem->next != NULL)
		delElem->next->prev = delElem->prev;
	if (delElem->prev != NULL)
		delElem->prev->next = delElem->next;
	free(delElem);
}

static void	ft_pushback_help(t_master **mst, t_master *tmp)
{
	tmp->t_connect = START;
	(*mst) = tmp;
	(*mst)->prev = NULL;
}

void	ft_pushback_m(t_master **master, int type_c, int type, int *end_head)
{
	t_master	*tmp;
	t_master	*last;

	last = ft_getlast_m(*master);
	tmp = (t_master *) malloc(sizeof(t_master));
	if (!tmp)
		return ;
	tmp->head = (*master)->head;
	tmp->groupe = (*master)->head->group;
	tmp->content = ft_generate_cont(&(tmp->head), &type);
	tmp->next = NULL;
	tmp->flag_del = 0;
	(*master)->head = tmp->head;
	if (!tmp->head)
		*end_head = 1;
	if (!last)
		ft_pushback_help(master, tmp);
	else
	{
		tmp->t_connect = type_c;
		last->next = tmp;
		tmp->prev = last;
	}
}
