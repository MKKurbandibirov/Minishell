/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:49:55 by magomed           #+#    #+#             */
/*   Updated: 2022/03/16 17:10:31 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/parser.h"

/*
**	Parser
*/
t_list	*crt_new_elm(char **cmd)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->cmd = cmd;
	new->next = NULL;
	return (new);
}

t_list	*stk_push_back(t_list *stk, char **cmd)
{
	t_list	*current;

	if (!stk)
	{
		stk = crt_new_elm(cmd);
		return (stk);
	}
	current = stk;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = (t_list *)malloc(sizeof(t_list));
	if (!current->next)
		return (NULL);
	current->next->cmd = cmd;
	current->next->next = NULL;
	return (stk);
}

t_list	*parse(char *cmd)
{
	t_list	*cmds;
	char	**tmp;
	int		i;
	
	tmp = ft_split(cmd, '|')
}


int main(int argc, char **argv, char **envr)
{
	char *command;
	while (1)
	{
		command = readline("Assalam_Aleykum:> ");
		if (check_quotes(command))
		{
			printf("Error!!!");
			break ;
		}
		add_history(command);
		command = enough_spaces(command);
		if (!command)
		{
			printf("Error!!!");
			break ;
		}
		printf("\n%s\n\n", command);
	}
	return (0);
}