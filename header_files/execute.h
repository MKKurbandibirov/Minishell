/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:18:52 by gtaggana          #+#    #+#             */
/*   Updated: 2022/07/04 17:04:18 by nfarfetc         ###   ########.fr       */
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

void	ft_pipe(char **cmd);
void	straight_redirect(char *filename);
void	reverse_redirect(char *filename);
void	double_reverse_reirect(char *filename);
void	heredoc(char *del);
void	replace_status(char **content);
char	*ft_here_dollar(char *s);

#endif
