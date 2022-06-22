/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 09:24:08 by gtaggana          #+#    #+#             */
/*   Updated: 2022/06/21 17:13:02 by nfarfetc         ###   ########.fr       */
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
	char		*pwd;
	char		*prompt;
	char		**cmd_path;
	int			return_status;
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
	int			type_connect;
	t_slave		*content;
	t_master	*next;
	t_master	*prev;
	t_plist		*head;
}	t_master;

#endif
