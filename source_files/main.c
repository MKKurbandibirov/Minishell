/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:49:55 by magomed           #+#    #+#             */
/*   Updated: 2022/05/02 13:12:18 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/minishell.h"

int main(int argc, char **argv, char **envr)
{
	char	*line;
	char	**cmd;
	while (1)
	{
		line = readline("Assalamu_Aleykum:> ");
		cmd = ft_split(line, ' ');
		
		if (ft_echo_n(cmd, 0) == 1)
			printf("%s\n", "echo with no '-n' flag!");
		add_history(line);
		
	}
	clear_history();
	return (0);
}