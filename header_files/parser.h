#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../header_files/minishell.h"

#define CMD 1
#define FLAG 2
#define ARG 3
#define OPER 4 //&& ||
#define HEREDOC 5 // <<
#define APPEND 6 // >>
#define IN 7// <
#define OUT 8//>
#define PIPE 10 //|
#define BG 11 //&

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

void	ft_pars(char *s1, int group, int add_len, int ie);
#endif