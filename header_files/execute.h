/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:42:51 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/06/21 17:13:13 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "minishell.h"
# include "struct.h"

void	path_parse(void);
char	*identify_cmd(char *cmd);

void	solo_cmd_exe(char **cmd);
void	ft_exe(void);

void	straight_redirect(char *filename);
void	reverse_redirect(char *filename);
void	double_reverse_reirect(char *filename);
void	here_doc(char *del);

#endif