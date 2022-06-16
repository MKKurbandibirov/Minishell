#include "../../header_files/minishell.h"

static void	ft_init_master(t_master *master)
{
	master->groupe = START;
	master->head = NULL;
	master->content = NULL;
	master->next = NULL;
	master->prev = NULL;

}
void	ft_generate_m(t_master **mst)
{
	int	type_c;
	int	t;

	t = 0;
	type_c = START;
	while ((*mst)->head != NULL)
	{
		ft_pushback_m(mst, type_c, t);
		type_c = (*mst)->head->type;
		ft_skip_opper(&(*mst)->head);
	}
}

void	ft_parser_v2(char *s)
{
	t_master	*master;

	master = malloc(sizeof(t_master));
	ft_init_master(master);
	if (ft_prevalidation(s))
		return ;
	ft_preparsing(master, s, 0, 0);
	//TODO VALIDATOR
	master = NULL;
	ft_generate_m(&master);
}