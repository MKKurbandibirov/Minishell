/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_list_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaggana <gtaggana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:18:22 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/06 13:35:32 by gtaggana         ###   ########.fr       */
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

void	ft_initparser(t_parser *env)
{
	env->head = NULL;
}

void	ft_remove_list(t_parser *env)
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
	{
		perror("Err malloc (PB)");
		exit(EXIT_FAILURE);
	}
	tmp->data = ft_strdup(data);
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
