/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:05:55 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:04:21 by nfarfetc         ###   ########.fr       */
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
# include <sys/types.h>
# include <dirent.h>
# include "../libft/libft.h"
# include "struct.h"
# include "readline/readline.h"
# include "readline/history.h"
# include "execute.h"
# include "builtins.h"
# include "parser.h"

extern t_minishell	*g_shell;

void	child_sig(void);
void	inter_sig(void);
void	main_sig(void);
char	*get_prompt(void);
void	free_global(void);
void	free_inter(char *line);
void	free_simple_list(t_list *lst);
int		ft_count_elem_in_start(t_list *lst);

t_list	*replace_star(char *pattern);

#endif
