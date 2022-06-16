#ifndef STRUCT_V2_H
# define STRUCT_V2_H

# include "minishell.h"

typedef struct s_plist t_plist;
typedef struct s_master t_master;
typedef struct s_slave t_slave;

typedef struct s_minishell
{
	t_list	*env;
	t_list	*exp;
	char	**cmd_path;
	int		return_status;
}	t_minishell;

typedef struct s_slave
{
	char			**cmd;
	int				type;
	int				type_connect;
	t_slave	*next;
	t_slave	*prev;
}	t_slave;

typedef struct s_master
{
	int				groupe;
	int				type_connect;
	t_slave			*content;
	t_master		*next;
	t_master		*prev;
	t_plist			*head;
}	t_master;

#endif