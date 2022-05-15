#include "../../header_files/minishell.h"

static t_plist	*ft_getLast(t_plist *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

static void	ft_delElem(t_plist **head, t_plist *delElem)
{
	if (*head == NULL || delElem == NULL)
		return ;
	if (*head == delElem)
		*head = delElem->next;
	if (delElem->next != NULL)
		delElem->next->prev= delElem->prev;
	if (delElem->prev != NULL)
		delElem->prev->next=delElem->next;
	free(delElem->data);
	free(delElem);
}

void	ft_initparser(t_parser *env)
{
	env->head = NULL;
}

void	ft_remove_list(t_parser *env)
{
	while (env->head)
		ft_delElem(&env->head, env->head);
}

void	ft_pushback_p(t_plist **head, char *data, int type, int group)
{
	t_plist	*tmp;
	t_plist	*last;

	last = ft_getLast(*head);
	tmp = (t_plist *) malloc(sizeof(t_plist));
	if (!tmp)
	{
		perror("Err malloc (PB)");
		exit(EXIT_FAILURE);
	}
	tmp->data = data;
	tmp->group = group;
	tmp->type = type;
	tmp->next = NULL;
	if (!last)
	{
		*head = tmp;
		(*head)->prev = NULL;
	}
	else
	{
		last->next = tmp;
		tmp->prev = last;
	}
}