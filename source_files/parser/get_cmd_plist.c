/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_plist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:23:24 by gtaggana          #+#    #+#             */
/*   Updated: 2022/07/04 17:01:19 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/parser.h"

static int	ft_count_arg_in_star(char *s)
{
	int		i;
	t_list	*lst;

	i = 0;
	lst = replace_star(s);
	i += ft_count_elem_in_start(lst);
	free_simple_list(lst);
	return (i);
}

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
			if (curr->type == ARG && ft_strchr(curr->data, '*') != NULL)
				i += ft_count_arg_in_star(curr->data);
			else
				i++;
			curr = curr->next;
		}
	}
	else
		i++;
	return (i);
}

static int	ft_haramshik(char **tmp, int i, t_list *lst)
{
	t_list	*curr;

	curr = lst;
	while (curr)
	{
		tmp[i++] = ft_strdup((char *) curr->content);
		curr = curr->next;
	}
	return (i);
}

static int	ft_get_cmd_contineu(char **tmp, t_plist **head, int i)
{
	tmp[i++] = ft_strdup((*head)->data);
	ft_delelem(head, *head);
	return (i);
}

char	**ft_get_cmd(t_plist **head, int i, int len)
{
	char	**tmp;
	t_list	*lst;

	tmp = (char **) malloc(sizeof(char *) * (ft_count_cmd_word(*head) + 1));
	i = 0;
	while (*head && ((*head)->type == CMD
			|| (*head)->type == FLAG || (*head)->type == ARG))
	{
		(void) len;
		if (ft_strchr((*head)->data, '*'))
		{
			lst = replace_star((*head)->data);
			i = ft_haramshik(tmp, i, lst);
			free_simple_list(lst);
		}
		else
			tmp[i++] = ft_strdup((*head)->data);
		ft_delelem(head, *head);
	}
	if (i == 0)
		i = ft_get_cmd_contineu(tmp, head, i);
	tmp[i] = NULL;
	return (tmp);
}
