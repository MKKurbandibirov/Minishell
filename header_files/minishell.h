/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:05:55 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/07 10:31:35 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>

# include "../libft/libft.h"
// # include "struct.h"
# include "struct_v2.h"
# include "readline/readline.h"
# include "readline/history.h"
# include "builtins.h"
// # include "parser.h"
# include "parser_v2.h"
# include "execute.h"

// typedef struct s_minishell
// {
// 	t_list	*env;
// 	t_list	*exp;
// 	char	**cmd_path;
// 	int		return_status;
// }	t_minishell;

extern t_minishell	*g_shell;

void	child_sig(void);
void	main_sig(void);
char	*get_prompt(void);

#endif
