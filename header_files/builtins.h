/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:03:15 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:04:09 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <limits.h>
# include "../libft/libft.h"
# include "minishell.h"

typedef struct s_key_val
{
	char	*key;
	char	*val;
}	t_key_val;

typedef int	(*t_cd_util)(char *path, t_list *env, t_list *exp);

int			ft_echo_n(char **cmd);
void		ft_pwd(void);

char		*get_pwd(t_list *env, int opt);
int			cd_home(char *path, t_list *env, t_list *exp);
int			cd_relative_home(char *path, t_list *env, t_list *exp);
int			cd_double_dot(char *path, t_list *env, t_list *exp);
int			cd_dot(char *path, t_list *env, t_list *exp);
int			cd_minus(char *path, t_list *env, t_list *exp);
int			cd_path(char *path, t_list *env, t_list *exp);
void		ft_cd(char *path, t_list *env, t_list *exp);

t_key_val	*create_env_node(char *env_i);
t_list		*get_envr(char **envr);
void		ft_env(t_list *my_env);

t_list		*get_expt(char **envr);
void		str_bubble(char **arr);
void		fill(t_list *c, char **s_arr);
char		**convert_to_strarr(t_list *list);
t_key_val	*create_exp_node(char *env_i, int option);
int			ft_export(char *cmd_1, t_list *exp, t_list *env);

int			ft_unset(t_list *env, t_list *exp, char **vars);

void		ft_exit(int return_stat, int opt);

void		free_list(t_list *lst);
int			builtin_parser(char **cmd, t_list *env, t_list *exp);
int			norm_helper(char **cmd, t_list *env, t_list *exp);

#endif