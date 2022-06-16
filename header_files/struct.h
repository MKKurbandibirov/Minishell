/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:04:27 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/16 18:18:36 by nfarfetc         ###   ########.fr       */
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
	char		*pwd;
	char		*prompt;
	char		**cmd_path;
	int			return_status;
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