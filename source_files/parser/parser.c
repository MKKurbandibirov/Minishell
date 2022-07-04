/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:23:29 by gtaggana          #+#    #+#             */
/*   Updated: 2022/07/04 17:08:33 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/parser.h"

static void	ft_init_master(t_master *master)
{
	master->flag_del = 0;
	master->groupe = START;
	master->head = NULL;
	master->content = NULL;
	master->next = NULL;
	master->prev = NULL;
}

t_master	*ft_generate_m(t_master *mst)
{
	int	type_c;
	int	t;
	int	end_head;

	t = 0;
	type_c = START;
	end_head = 0;
	while (mst->head != NULL && end_head == 0)
	{
		ft_pushback_m(&mst, type_c, t, &end_head);
		if (end_head == 0)
		{
			type_c = mst->head->type;
			ft_skip_opper(&mst->head);
		}
	}
	return (mst);
}

int	ft_parser_v2(char *s)
{
	t_master	master;

	if (!s)
		return (1);
	ft_init_master(&master);
	if (ft_prevalidation(s))
		return (1);
	ft_preparsing(&master, s, 0, 0);
	if (ft_validator(master.head))
		return (1);
	g_shell->master = ft_generate_m(&master);
	return (0);
}
