/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_plist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaggana <gtaggana@student.21-school       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 09:23:05 by gtaggana          #+#    #+#             */
/*   Updated: 2022/06/20 09:23:07 by gtaggana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/parser.h"

static int	ft_count_cmd_word(t_plist *prs)
{
	int		i;
	t_plist	*curr;

	curr = prs;
	i = 0;
	if (curr->type == CMD)
	{
		while (curr && (curr->type == CMD
				|| curr->type == FLAG || curr->type == ARG))
		{
			i++;
			curr = curr->next;
		}
	}
	else
		i++;
	return (i);
}

char	**ft_get_cmd(t_plist **head)
{
	char	**tmp;
	int		i;

	tmp = (char **) malloc(sizeof(char *) * (ft_count_cmd_word(*head) + 1));
	i = 0;
	while (*head && ((*head)->type == CMD
			|| (*head)->type == FLAG || (*head)->type == ARG))
	{
		tmp[i++] = ft_strdup((*head)->data);
		ft_delelem(head, *head);
	}
	if (i == 0)
	{
		tmp[i++] = ft_strdup((*head)->data);
		ft_delelem(head, *head);
	}
	tmp[i] = NULL;
	return (tmp);
}
