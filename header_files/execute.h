/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:42:51 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/05/10 10:25:27 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

void	path_parse(void);
char	*identify_cmd(char *cmd);
void	solo_cmd_exec(char **cmd, int fd_in, int fd_out);

void	and_exec(char **cmd1, char **cmd2, int fd_in, int fd_out);
#endif