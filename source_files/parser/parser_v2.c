#include "../../header_files/minishell.h"

static void	ft_init_master(t_master *master)
{
	master->groupe = START;
	master->head = NULL;
	master->content = NULL;
	master->next = NULL;
	master->prev = NULL;
}

void	ft_parser_v2(char *s)
{
	t_master	master;

	ft_init_master(&master);
	if (ft_prevalidation(s))
		return ;
	ft_preparsing(&master, s, 0, 0);
}