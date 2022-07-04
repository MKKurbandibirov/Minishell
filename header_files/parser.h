/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:01:45 by gtaggana          #+#    #+#             */
/*   Updated: 2022/07/04 17:05:08 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "minishell.h"

# define START 0
# define AND 11 //&&
# define ELSE 12 //||
# define OLD_TYPE 13

# define CMD 1
# define FLAG 2
# define ARG 3

# define PIPE 4 // |
# define BG 5 // &

# define INFILE_RE 6 // <
# define OUTFILE_RE 7 // >
# define HEREDOC 8 // <<
# define APPEND 9 // >>

# define ERR -123

typedef struct s_plist
{
	char			*data;
	int				type;
	int				group;
	struct s_plist	*next;
	struct s_plist	*prev;
}	t_plist;

typedef struct s_parser
{
	t_plist		*head;
}	t_parser;

int			ft_parser_v2(char *s);

//utils_v2.c
void		ft_err_msg(char *msg);
char		*ft_srch_pair_quote(char *s, int c);
char		*ft_env_search(char *dollar);
char		*ft_ifdollar(char *s, int *len);
int			ft_isspec(char c);

//utils_v2_1.c
char		*ft_check_scpec(char *s, int *add);
int			ft_check_type_first_arg(char *s, char c);
int			ft_check_4_redir(char *s);
char		*ft_argv_am(char *s, int *add);
int			ft_checking_cause(char *s, int *grp, t_master *prs, int i);

//utils2.c
void		ft_checking_help(char *s, int *grp, t_master *prs, int *i);

//quote_v2.c
char		*ft_single_quote(char *s);
char		*ft_dbl_quote(char *s);

//prevalidato_v2.c
int			ft_prevalidation(char *s);
int			ft_skip_quote(char *s);

//substitution_v2.c
char		*ft_substitution(char *s, int pt);

//prepars_list_func_v2.c
void		ft_delelem(t_plist **head, t_plist *delElem);
void		ft_remove_prerars_list(t_master *env);
void		ft_pushback_p(t_plist **head, char *data, int type, int group);
t_plist		*ft_getlast(t_plist *head);

//master_2.c 
t_master	*ft_getlast_m(t_master *head);
void		ft_pushback_m(t_master **master, int type_c, int type,
				int *end_head);
void		ft_delelem_m(t_master **head, t_master *delElem);

//slave_v2.c
t_slave		*ft_generate_cont(t_plist **head, int *t);

//slaveLST_v2.c
t_slave		*ft_getlast_s(t_slave *head);
void		ft_pushback_s(t_slave **slave, int type, int type_c, char **cmd);
void		ft_insert_penult(t_slave **slave, int type, int type_c, char **cmd);
int			ft_skip_opper(t_plist **head);
void		ft_delelem_s(t_slave **head, t_slave *delElem);

//preparsing_v2.c
void		ft_preparsing(t_master *master, char *s, int i, int add_len);

//get_cmd_plist_v2.c
char		**ft_get_cmd(t_plist **head, int i, int len);

//validator.c
int			ft_validator(t_plist *prs);
#endif
