#include "../header_files/minishell.h"
///////////////////////////////////////////////////////////////////////////////////////////////
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
		return;
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
//////////////////////////////////////////////////////////////////////////////////////////////////
void	ft_strncpy(char *src, char *direc, int len)
{
	char	*tmp;

	tmp = src;
	if (len)
	{
		while (len - 1 > 0 && *tmp)
		{
			*direc++ = *tmp++;
			len--;
		}
		*direc = '\0';
	}
}

int	ft_isspace(char c)
{
	if ( c == ' ' || c == '\t' || c == '\n'
		|| c == '\n' || c == '\r' || c == '\v')
		return (1);
	return (0);
}

int	ft_validate_pairs(char *s)
{
	int		i;
	int		status;
	char	last_c;

	i = -1;
	status = 0;
	last_c = s[0];
	while (s[++i])
	{
		if (s[i] == '(' && last_c != ')')
			status++;
		else if (s[i] == ')' && status > 0 && last_c != '(')
			status--;
		else if ((s[i] == ')' && status == 0)
			|| (s[i] == '(' && last_c == ')')
			|| (s[i] == ')' && last_c == '('))
			return (1);
		if (!ft_isspace(s[i]))
			last_c = s[i];
	}
	return (status);
}

char	*ft_env_search(char *dollar)
{
	t_list	*curr;
	int		i;

	curr = g_shell->env;
	while (curr != NULL)
	{
		if (!ft_strcmp(((t_key_val *)curr->content)->key, dollar))
			break ;
		curr = curr->next;
	}
	if (!curr)
		return (NULL);
	return (((t_key_val *)curr->content)->val);
}

char	*ft_ifdollar(char *s, int *len)
{
	char	*dollar;
	char	*ret;

	*len = 0;
	while (s[*len] && (ft_isalpha(s[*len]) || ft_isdigit(s[*len]))
		&& (!ft_isspace(s[*len])))
		(*len)++;
	dollar = (char *) malloc(sizeof(char) * (*len) + 1);
	ft_strncpy(s, dollar, *(len) + 1);
	ret = ft_env_search(dollar);
	free(dollar);
	return (ret);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
char	*ft_dbl_quotes_subsit(char *s)
{
	int		pt;
	int		add_len;
	char	*dlr;
	char	*ret;

	pt = -1;
	ret = ft_substr("", 0, 1);
	while (s[++pt])
	{
		if (s[pt] == '$' && s[pt + 1]
			&& (ft_isalpha(s[pt + 1]) || ft_isdigit(s[pt + 1])))
		{
			dlr = ft_ifdollar(&s[++pt], &add_len);
			pt += (add_len - 1);
			if (!dlr)
				continue ;
			ret = ft_strjoin_free(ret, dlr, 3);
		}
		else
			ret = ft_strjoin_c_free(ret, s[pt]);
	}
	return (ret);
}

char	*ft_dbl_replacement(char *s)
{
	int		len;
	int		pt;
	int		new_len;
	char	*new;

	pt = -1;
	new_len = 0;
	while (s[++pt])
	{
		if (s[pt] != '\\' && s[pt + 1] && s[pt + 1] != '\"')
			new_len++;
	}
	new = (char *)malloc(sizeof(char) * new_len + 1);
	pt = -1;
	new_len = 0;
	while (s[++pt])
	{
		if (s[pt] == '\\' && s[pt + 1] && s[pt + 1] == '\"')
			continue ;
		new[new_len++] = s[pt];
	}
	new[new_len] = '\0';
	free(s);
	return (new);
}

char	*ft_srch_pair_quote(char *s, int c)
{
	int	i;
	int	f_i;

	i = 0;
	f_i = -1;
	while (s[i] != 0)
	{
		if (s[i] == c && s[i-1] != '\\')
		{
			f_i = i;
			break ;
		}
		i++;
	}
	if (c == '\0')
		return (&s[i]);
	else if (f_i == -1)
		return (NULL);
	else
		return (&s[f_i]);
}

char	*ft_dbl_quoteProccessing(char *s, int *add)
{
	char	*next_c;
	char	*ret;
	int		len;

	len = 0;
	next_c = ft_srch_pair_quote(&s[1], s[0]);
	if (next_c == NULL)
		printf("INCORRECT");
	else
	{
		len += next_c - &s[len];
		ret = malloc(len + 1);
		ft_strncpy(&s[1], ret, len);
		ret = ft_dbl_replacement(ret);
		//ret = ft_dbl_quotes_subsit(ret);
		*add = len;
	}
	return (ret);
}

char	*ft_single_quote(char *s, int *add)
{
	char	*next_c;
	char	*ret;
	int		len;

	len = 0;
	next_c = ft_strchr(&s[1], s[0]);
	if (next_c == NULL)
		printf("INCORRECT");
	else
	{
		len += next_c - &s[len];
		ret = malloc(len + 1);
		ft_strncpy(&s[1], ret, len);
		*add = len;
	}
	return (ret);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
char	*ft_argv_am(char *s, int *add)
{
	int		i;
	char	*ret;

	i = 0;
	while (s[i] && !ft_isspace(s[i]) && s[i] != '&'
		&& s[i] != '|' && s[i] != ')' && s[i] != '<'
		&& s[i] != '>')
		i++;
	*add = i;
	ret = (char *) malloc(sizeof(char) * i + 1);
	ft_strncpy(s, ret, i + 1);
	return (ret);
}

int	ft_checking_cause(char *s, int *grp, t_parser *prs)
{
	int add;

	add = 0;
	if (s[0])
	{
		add++;
		if (s[0] == ')')
			(*grp)++;
		else if (s[0] == '|' && (!s[1] || s[1] != '|'))
			ft_pushback_p(&prs->head, "|", PIPE, *grp);
		else if (s[0] == '&' && (!s[1] || s[1] != '&'))
			ft_pushback_p(&prs->head, "&", BG, *grp);
		else
			add++;
		if (s[0] == '|' && s[1] && s[1] == '|')
			ft_pushback_p(&prs->head, "||", OPER, *grp);
		else if (s[0] == '&' && s[1] && s[1] == '&')
			ft_pushback_p(&prs->head, "&&", OPER, *grp);
	}
	return (add);
}

int	ft_get_arg_continue(char *s, int *group, t_parser *prs)
{
	int	add; 

	add = 0;
	if (s[0] && s[0] == '<' && s[1] && s[1] == '<')
	{
		ft_pushback_p(&prs->head, "<<", HEREDOC, *group);
		add+=2;
	}
	else if (s[0] && s[0] == '>' && s[1] && s[1] == '>')
	{
		ft_pushback_p(&prs->head, ">>", APPEND, *group);
		add+=2;
	}
	else if (s[0] && s[0] == '>')
	{
		ft_pushback_p(&prs->head, ">", OUT, *group);
		add++;
	}
	else if (s[0] && s[0] == '<')
	{
		ft_pushback_p(&prs->head, "<", IN, *group);
		add++;
	}
	return (add);
}

int	ft_get_arg(char *s, int *group, t_parser *prs, int i)
{
	int	add; 

	while (s[i] && s[i] != '&' && s[i] != '|' && s[i] != ')')
	{
		while (s[i] && (ft_isspace(s[i]) || s[i] == '('))
			i++;
		add = 0;
		if (s[i] && s[i] == '-')
			ft_pushback_p(&prs->head, ft_argv_am(&s[i], &add), FLAG, *group);
		else if (s[i] && s[i] == '\'')
			ft_pushback_p(&prs->head, ft_single_quote(&s[i], &add),
				ARG, *group);
		else if (s[i] && s[i] == '\"')
			ft_pushback_p(&prs->head, ft_dbl_quoteProccessing(&s[i], &add),
				ARG, *group);
		else
			add = ft_get_arg_continue(&s[i], group, prs);
		if (add == 0)
			ft_pushback_p(&prs->head, ft_argv_am(&s[i], &add), ARG, *group);
		i += add;
		while (s[i] && (ft_isspace(s[i]) || s[i] == '('))
			i++;
	}
	i += ft_checking_cause(&s[i], group, prs);
	return (i);
}

void	ft_clear_parslst(t_parser *prs, char *s)
{
	t_plist	*curr;

	curr = prs->head;
	while (curr)
	{
		if (curr->data[0] == '\0')
			ft_delElem(&prs->head, curr);
		curr = curr->next;
	}
	free(s);
}

char	*ft_substitution(char *s, int pt)
{
	int		add_len;
	char	*test;
	char	*ret;

	ret = ft_substr("", 0, 1);
	while (s[++pt])
	{
		test = NULL;
		add_len = 1;
		if (s[pt] == '$' && s[pt + 1]
			&& (ft_isalpha(s[pt + 1]) || ft_isdigit(s[pt + 1])))
			test = ft_ifdollar(&s[++pt], &add_len);
		else if (s[pt] == '\'')
			test = ft_single_quote(&s[pt], &add_len);
		else if (s[pt] == '\"')
			test = ft_single_quote(&s[pt], &add_len);
		else
			ret = ft_strjoin_c_free(ret, s[pt]);
		if (test)
			ret = ft_strjoin_free(ret, test, 3);
		pt += (add_len - 1);
	}
	return (ret);
}

int	ft_validator(t_plist *curr)
{
	while (curr && curr->type == CMD)
	{
		curr = curr->next;
		while (curr != NULL && (curr->type == FLAG || curr->type == ARG))
			curr = curr->next;
		if (curr != NULL && (curr->type == OUT || curr->type == APPEND))
		{
			curr = curr->next;
			if (curr->type == ARG)
				curr = curr->next;
			else
				return (EXIT_FAILURE);
		}
		if (curr  != NULL && (curr->type == PIPE
				|| curr->type == OPER || curr->type == BG))
			curr = curr->next;
	}
	if (curr == NULL)
		return (0);
	return (EXIT_FAILURE);
}

void	ft_pars(char *s1, int group, int add_len, int i)
{
	t_parser	prs;
	char		*s;

	ft_initparser(&prs);
	if (ft_validate_pairs(s1) != 0)
	{
		printf("ERR NOT VALID STR! ()");
		return ;
	}
	s = ft_substitution(s1, -1);
	while (s[i])
	{
		while (ft_isspace(s[i]) || s[i] == '(')
			i++;
		if (s[i] && s[i] != ')')
		{
			ft_pushback_p(&prs.head, ft_argv_am(&s[i], &add_len), CMD, group);
			i += (add_len);
		}
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i])
			i += (ft_get_arg(&s[i], &group, &prs, 0) - 1);
		i++;
	}
	ft_clear_parslst(&prs, s);
	if (ft_validator(prs.head) == 0)
		printf("OK\n");
	else
		printf("FUCK\n");
}
