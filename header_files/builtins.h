/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:03:15 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/05/04 13:51:56 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <limits.h>
# include "../libft/libft.h"

typedef struct s_key_val
{
	char	*key;
	char	*value;
}	t_key_val;

int			ft_echo_n(char **cmd, int fd);
void		ft_pwd(int fd);
void		ft_cd(char *path, int fd);

t_key_val	*create_env_node(char *env_i);
t_list		*get_envr(char **envr);
void		ft_env(t_list *my_env, int fd);

t_list		*get_expt(char **envr);
int			ft_export(char **cmd, t_list *exp, t_list *env, int fd);

#endif