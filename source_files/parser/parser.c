/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:10:09 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/16 18:20:21 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/parser.h"

static void	ft_init_master(t_master *master)
{
	master->groupe = START;
	master->head = NULL;
	master->content = NULL;
	master->next = NULL;
	master->prev = NULL;
}

t_master	ft_generate_m(t_master *mst)
{
	int	type_c;
	int	t;

	t = 0;
	type_c = START;
	while (mst->head != NULL)
	{
		ft_pushback_m(&mst, type_c, t);
		if (mst->head != NULL)
		{
			type_c = mst->head->type;
			ft_skip_opper(&mst->head);
		}
	}
	return (*mst);
}

void	ft_parser_v2(char *s)
{
	t_master	master;

	ft_init_master(&master);
	if (ft_prevalidation(s))
		return ;
	ft_preparsing(&master, s, 0, 0);
	//TODO VALIDATOR
	master = ft_generate_m(&master);
	g_shell->master = &master;
}
