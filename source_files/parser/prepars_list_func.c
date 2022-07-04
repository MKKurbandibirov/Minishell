/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepars_list_func.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:23:34 by gtaggana          #+#    #+#             */
/*   Updated: 2022/07/04 17:08:35 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/parser.h"

t_plist	*ft_getlast(t_plist *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	ft_insert_after(t_plist *prev_node, char *data, int group, int type)
{
	t_plist	*new;

	new = (t_plist *)malloc(sizeof(t_plist));
	new->data = ft_strdup(data);
	new->group = group;
	new->type = type;
	new->next = prev_node->next;
	prev_node->next = new;
	new->prev = prev_node;
	if (new->next != NULL)
		new->next->prev = new;
}

void	ft_delelem(t_plist **head, t_plist *delElem)
{
	if (*head == NULL || delElem == NULL)
		return ;
	if (*head == delElem)
		*head = delElem->next;
	if (delElem->next != NULL)
		delElem->next->prev = delElem->prev;
	if (delElem->prev != NULL)
		delElem->prev->next = delElem->next;
	free(delElem->data);
	free(delElem);
}

void	ft_remove_prerars_list(t_master *env)
{	
	while (env->head)
		ft_delelem(&env->head, env->head);
}

void	ft_pushback_p(t_plist **head, char *data, int type, int group)
{
	t_plist	*tmp;
	t_plist	*last;

	last = ft_getlast(*head);
	tmp = (t_plist *) malloc(sizeof(t_plist));
	if (!tmp)
		return ;
	tmp->data = data;
	tmp->group = group;
	tmp->type = type;
	tmp->next = NULL;
	if (!last)
	{
		*head = tmp;
		(*head)->prev = NULL;
	}
	else
	{
		last->next = tmp;
		tmp->prev = last;
	}
}
