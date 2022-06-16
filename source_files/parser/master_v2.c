#include "../../header_files/minishell.h"

t_master	*ft_getlast_m(t_master *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	ft_pushback_m(t_master *master, int type_c, int type)
{
	t_master	*tmp;
	t_master	*last;

	last = ft_getlast_m(master);
	tmp = (t_master *) malloc(sizeof(t_master));
	if (!tmp)
	{
		perror("Err malloc (PB)");
		exit(EXIT_FAILURE);
	}
	ft_generate_cont(master->head, &master, &type);
	tmp->groupe = master->head->group;
	tmp->next = NULL;
	if (!last)
	{
		master->type_connect = START;
		master = tmp;
		master->prev = NULL;
	}
	else
	{
		master->type_connect = type_c;
		last->next = tmp;
		tmp->prev = last;
	}
}