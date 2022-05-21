/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:34:03 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/05/21 10:25:43 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../header_files/minishell.h"

# define CMD 1
# define FLAG 2
# define ARG 3
# define OPER 4 // && ||
# define HEREDOC 5 // <<
# define APPEND 6 // >>
# define IN 7 // <
# define OUT 8 // >
# define PIPE 10 // |
# define BG 11 // &

typedef struct s_plist	t_plist;
typedef struct s_cmds	t_cmds;
typedef struct s_parser	t_parser;

struct s_plist
{
	char	*data;
	int		type;
	int		group;
	t_plist	*next;
	t_plist	*prev;
};

struct s_parser
{
	t_plist		*head;
};

t_plist	*ft_getlast(t_plist *head);
void	ft_delelem(t_plist **head, t_plist *delElem);
void	ft_pushback_p(t_plist **head, char *data, int type, int group);
void	ft_remove_list(t_parser *env);
void	ft_initparser(t_parser *env);
char	*ft_substitution(char *s, int pt);
char	*ft_env_search(char *dollar);
char	*ft_ifdollar(char *s, int *len);
char	*ft_argv_am(char *s, int *add);
int		ft_checking_cause(char *s, int *grp, t_parser *prs);
int		ft_get_arg_continue(char *s, int *group, t_parser *prs);
int		ft_get_arg(char *s, int *group, t_parser *prs, int i);
void	ft_clear_parslst(t_parser *prs, char *s);
char	*ft_dbl_quotes_subsit(char *s);
char	*ft_dbl_replacement(char *s);
char	*ft_srch_pair_quote(char *s, int c);
char	*ft_dbl_quoteproccessing(char *s, int *add);
char	*ft_single_quote(char *s, int *add);
int		ft_validate_pairs(char *s);
int		ft_validator(t_plist *curr);

void	ft_pars(char *s1, int group, int add_len, int ie);
#endif