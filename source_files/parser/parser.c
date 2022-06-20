/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: gtaggana <gtaggana@student.21-school       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 09:22:42 by gtaggana          #+#    #+#             */
/*   Updated: 2022/06/20 09:22:46 by gtaggana         ###   ########.fr       */
=======
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:10:09 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/16 19:40:38 by nfarfetc         ###   ########.fr       */
>>>>>>> main
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

t_master	*ft_generate_m(t_master *mst)
{
	int	type_c;
	int	t;
<<<<<<< HEAD
	int	end_head;

	t = 0;
	type_c = START;
	end_head = 0;
	while (mst->head != NULL && end_head == 0)
	{
		ft_pushback_m(&mst, type_c, t, &end_head);
		if (end_head == 0)
=======

	t = 0;
	type_c = START;
	while (mst->head != NULL)
	{
		ft_pushback_m(&mst, type_c, t);
		if (mst->head != NULL)
>>>>>>> main
		{
			type_c = mst->head->type;
			ft_skip_opper(&mst->head);
		}
	}
	return (mst);
}

void	ft_parser_v2(char *s)
{
	t_master	master;

	ft_init_master(&master);
	if (ft_prevalidation(s))
		return ;
	ft_preparsing(&master, s, 0, 0);
<<<<<<< HEAD
=======
	//TODO VALIDATOR
>>>>>>> main
	g_shell->master = ft_generate_m(&master);
}
