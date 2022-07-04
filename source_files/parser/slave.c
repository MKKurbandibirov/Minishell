/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:23:52 by gtaggana          #+#    #+#             */
/*   Updated: 2022/07/04 17:08:46 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_files/minishell.h"

static void	ft_redirect_case(t_plist **head, t_slave **sl, int type_c)
{
	int		type;
	char	**cmd;

	type = ft_skip_opper(head);
	if ((*sl) == NULL || ((*sl)->prev && ((*sl)->prev->type == PIPE
				|| ((*sl)->prev->type >= 6 && (*sl)->prev->type <= 9)
				|| ((*sl)->prev->type == 11 || (*sl)->prev->type == 12))))
	{
		cmd = malloc(sizeof(char *) * 2);
		cmd[0] = ft_strdup((*head)->data);
		cmd[1] = NULL;
		ft_delelem(head, *head);
		ft_pushback_s(sl, type, type_c, cmd);
	}
	else
	{
		ft_insert_penult(sl, type, type_c, ft_get_cmd(head, 0, 0));
	}
}

static void	ft_command_case(t_plist **head, t_slave **sl, int type_c)
{
	int		type;
	char	**cmd;

	type = (*head)->type;
	cmd = ft_get_cmd(head, 0, 0);
	ft_pushback_s(sl, type, type_c, cmd);
}

static void	ft_pipe_case(t_plist **head, t_slave **sl)
{
	int		type;
	t_slave	*last;

	last = ft_getlast_s(*sl);
	type = ft_skip_opper(head);
	last->type = type;
}

static void	ft_connection_case(t_plist **head, int *type_c)
{
	int	type;

	type = ft_skip_opper(head);
	*type_c = type;
}

t_slave	*ft_generate_cont(t_plist **head, int *t)
{
	int		start_group;
	t_slave	*sl;

	sl = NULL;
	start_group = (*head)->group;
	*t = START;
	while ((*head) != NULL && start_group == (*head)->group)
	{
		if ((*head)->type >= 6 && (*head)->type <= 9)
			ft_redirect_case(head, &sl, *t);
		if ((*head) && (*head)->type == CMD)
			ft_command_case(head, &sl, *t);
		if ((*head) && (*head)->type == PIPE)
			ft_pipe_case(head, &sl);
		if ((*head) && (*head)->group == start_group
			&& ((*head)->type == AND || (*head)->type == ELSE))
			ft_connection_case(head, t);
	}
	return (sl);
}
