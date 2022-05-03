/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:24:54 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/05/03 12:17:44 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/builtins.h"

void	ft_env(t_list *my_env, int fd)
{
	t_list	*curr;
	
	curr = my_env;
	while (curr->next != NULL)
	{
		write(fd, ((t_env *)curr->content)->key, ft_strlen(((t_env *)curr->content)->key));
		write(fd, "=", 1);
		write(fd, ((t_env *)curr->content)->value, ft_strlen(((t_env *)curr->content)->value));
		write(fd, "\n", 1);
		curr = curr->next;
	}
}