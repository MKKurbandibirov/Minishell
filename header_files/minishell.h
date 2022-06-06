/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:05:55 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/06 14:42:45 by nfarfetc         ###   ########.fr       */
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

# include "readline/readline.h"
# include "readline/history.h"
# include "builtins.h"
# include "execute.h"
# include "parser.h"
# include "../libft/libft.h"

typedef struct s_minishell
{
	t_list	*env;
	t_list	*exp;
	char	**cmd_path;
	int		return_status;
}	t_minishell;

t_minishell	*g_shell;

void	child_sig(void);
void	main_sig(void);
char	*get_prompt(void);

#endif
