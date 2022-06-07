/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:47:13 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/07 14:59:48 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// typedef struct s_cmds	t_cmds;

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

// typedef enum e_cmd_type
// {
// 	PIPE,
// 	SOLO,
// }	t_cmd_type;

// typedef struct s_cmds
// {
// 	char			**cmd;
// 	t_cmd_type		type;
// }	t_cmds;

#endif