/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaggana <gtaggana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 09:05:14 by magomed           #+#    #+#             */
/*   Updated: 2022/06/06 13:21:05 by gtaggana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/minishell.h"

char    *get_prompt(void)
{
    t_list  *curr;
    int     i;
    char    *prompt;
    char    **pwd;

    curr = g_shell->env;
    pwd = NULL;
    while (curr != NULL)
    {
        if (!ft_strcmp(((t_key_val *)curr->content)->key, "PWD"))
            pwd = ft_split(((t_key_val *)curr->content)->val, '/');
        curr = curr->next;
    }
    if (pwd)
    {
        i = 0;
        while (pwd[i + 1])
            i++;
        prompt = ft_strjoin(pwd[i], ":> ");
        free_split(pwd);
        return (prompt);
    }
    return (NULL);
}