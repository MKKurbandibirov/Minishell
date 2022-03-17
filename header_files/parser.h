/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 10:47:21 by magomed           #+#    #+#             */
/*   Updated: 2022/03/16 17:06:51 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "readline/readline.h"
# include "readline/history.h"

// # define REDIRECT_IN "<"
// # define REDIRECT_OUT ">"
// # define APPEND ">>"
// # define HERE_DOC "<<"

enum {
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,
	STATE_GENERAL,
};

typedef struct s_list
{
	char			**cmd;
	struct s_list	*next;
}	t_list;

char	**ft_split(char const *s, char c);
void	free_split(char **res);

int		check_quotes(char *cmd);
char	*enough_spaces(char *cmd);

#endif