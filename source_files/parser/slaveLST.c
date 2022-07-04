/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slaveLST.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:24:03 by gtaggana          #+#    #+#             */
/*   Updated: 2022/07/04 17:08:48 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/minishell.h"

t_slave	*ft_getlast_s(t_slave *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	ft_pushback_s(t_slave **slave, int type, int type_c, char **cmd)
{
	t_slave	*tmp;
	t_slave	*last;

	last = ft_getlast_s(*slave);
	tmp = (t_slave *) malloc(sizeof(t_slave));
	if (!tmp)
		return ;
	tmp->cmd = cmd;
	tmp->type = type;
	tmp->type_connect = type_c;
	tmp->next = NULL;
	if (!last)
	{
		*slave = tmp;
		(*slave)->prev = NULL;
	}
	else
	{
		last->next = tmp;
		tmp->prev = last;
	}
}

void	ft_delelem_s(t_slave **head, t_slave *delElem)
{
	if (*head == NULL || delElem == NULL)
		return ;
	if (*head == delElem)
		*head = delElem->next;
	if (delElem->next != NULL)
		delElem->next->prev = delElem->prev;
	if (delElem->prev != NULL)
		delElem->prev->next = delElem->next;
	free_split(delElem->cmd);
	free(delElem);
}

void	ft_insert_penult(t_slave **slave, int type, int type_c, char **cmd)
{
	t_slave	*new;
	t_slave	*last;

	last = ft_getlast_s(*slave);
	new = (t_slave *)malloc(sizeof(t_slave));
	new->cmd = cmd;
	new->type_connect = type_c;
	new->type = type;
	new->next = last;
	if (last->prev == NULL)
	{
		last->prev = new;
		new->prev = NULL;
		*slave = new;
	}
	else
	{
		last->prev->next = new;
		new->prev = last->prev;
	}
	if (new->next != NULL)
		new->next->prev = new;
}

int	ft_skip_opper(t_plist **head)
{
	char	**del;
	int		type;

	type = (*head)->type;
	del = ft_get_cmd(head, 0, 0);
	free_split(del);
	return (type);
}
