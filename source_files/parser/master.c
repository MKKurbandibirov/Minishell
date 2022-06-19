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
	if (head->next == NULL && head->content == NULL)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	ft_delelem_m(t_master **head, t_master *delElem)
{
	if (*head == NULL || delElem == NULL)
		return ;
	if (*head == delElem)
		*head = delElem->next;
	if (delElem->next != NULL)
		delElem->next->prev = delElem->prev;
	if (delElem->prev != NULL)
		delElem->prev->next = delElem->next;
	free(delElem);
}

void	ft_pushback_m(t_master **master, int type_c, int type, int *end_head)
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
	if (!tmp->head)
		*end_head = 1;
	if (!last)
	{
		tmp->type_connect = START;
		(*master) = tmp;
		(*master)->prev = NULL;
	}
	else
	{
		tmp->type_connect = type_c;
		last->next = tmp;
		tmp->prev = last;
	}
}
