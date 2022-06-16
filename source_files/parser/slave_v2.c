#include "../../header_files/minishell.h"

static void	ft_redirect_case(t_plist *head, t_master **mst, int type_c)
{
	int		type;

	type = ft_skip_opper(&head);
	if ((*mst)->content == NULL || ((*mst)->content->prev && ((*mst)->content->prev->type == PIPE
		|| ((*mst)->content->prev->type >= 6 && (*mst)->content->prev->type <= 9)
			|| ((*mst)->content->prev->type == 11 || (*mst)->content->prev->type == 12))))
	{
		ft_pushback_s((*mst)->content, type, type_c, ft_get_cmd(&head));
	}
	else
	{
		ft_insert_penult((*mst)->content, type, type_c, ft_get_cmd(&head));
	}
}

static void	ft_command_case(t_plist *head, t_master *mst, int type_c)
{
	int		type;
	char	**cmd;

	type = head->type;
	cmd = ft_get_cmd(&head);
	ft_pushback_s(mst->content, type, type_c, cmd);
}

static void	ft_pipe_case(t_plist *head, t_master *mst)
{
	int		type;

	type = ft_skip_opper(&head);
	mst->content->prev->type = type;
}

static void	ft_connection_case(t_plist *head, int *type_c)
{
	int	type;

	type = ft_skip_opper(&head);
	*type_c = type;
}

void	ft_generate_cont(t_plist *head, t_master **mst, int *t)
{
	int		start_group;

	start_group = head->group;
	*t = START;
	while(head != NULL && start_group == head->group)
	{
		if (head->type >= 6 && head->type <=9)
			ft_redirect_case(head, mst, *t);
		if (head && head->type == CMD)
			ft_command_case(head, *mst, *t);
		if (head && head->type == PIPE)
			ft_pipe_case(head, *mst);
		if (head && head->group == start_group && (head->type == AND || head->type == ELSE))
			ft_connection_case(head, t);
	}
}