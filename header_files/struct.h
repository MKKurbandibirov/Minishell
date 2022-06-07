#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

typedef struct s_minishell
{
	t_list	*env;
	t_list	*exp;
	char	**cmd_path;
	int		return_status;
}	t_minishell;


// typedef struct s_plist	t_plist;
typedef struct s_cmds	t_cmds;
// typedef struct s_parser	t_parser;

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

#endif