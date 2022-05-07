/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:05:55 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/05/07 15:33:31 by nfarfetc         ###   ########.fr       */
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
# include "../libft/libft.h"

typedef struct s_minishell
{
	t_list	*env;
	t_list	*exp;
	char	**cmd_path;
	int		return_status;
}	t_minishell;

t_minishell	*g_shell;

void	path_parse(void); // Not Here
char	*identify_cmd(char *cmd); // Not Here

#endif
