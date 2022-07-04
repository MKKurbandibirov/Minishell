/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:23:11 by gtaggana          #+#    #+#             */
/*   Updated: 2022/07/04 17:05:17 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

typedef struct s_plist	t_plist;
typedef struct s_master	t_master;
typedef struct s_slave	t_slave;

typedef struct s_minishell
{
	t_list		*env;
	t_list		*exp;
	t_master	*master;
	t_list		*pids;
	t_list		*heredoc;
	char		*pwd;
	char		*prompt;
	char		**cmd_path;
	int			ret_stat;
	int			std_in;
	int			std_out;
}	t_minishell;

typedef struct s_slave
{
	char	**cmd;
	int		type;
	int		type_connect;
	t_slave	*next;
	t_slave	*prev;
}	t_slave;

typedef struct s_master
{
	int			groupe;
	int			t_connect;
	int			flag_del;
	t_slave		*content;
	t_master	*next;
	t_master	*prev;
	t_plist		*head;
}	t_master;

#endif
