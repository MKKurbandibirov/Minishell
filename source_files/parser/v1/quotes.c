// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   quotes.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/05/21 09:19:14 by nfarfetc          #+#    #+#             */
// /*   Updated: 2022/05/26 16:06:22 by magomed          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../header_files/parser.h"

// char	*ft_dbl_quotes_subsit(char *s)
// {
// 	int		pt;
// 	int		add_len;
// 	char	*dlr;
// 	char	*ret;

// 	pt = -1;
// 	ret = ft_substr("", 0, 1);
// 	while (s[++pt])
// 	{
// 		if (s[pt] == '$' && s[pt + 1]
// 			&& (ft_isalpha(s[pt + 1]) || ft_isdigit(s[pt + 1])))
// 		{
// 			dlr = ft_ifdollar(&s[++pt], &add_len);
// 			pt += (add_len - 1);
// 			if (!dlr)
// 				continue ;
// 			ret = ft_strjoin_free(ret, dlr, 3);
// 		}
// 		else
// 			ret = ft_strjoin_c_free(ret, s[pt]);
// 	}
// 	return (ret);
// }

// char	*ft_dbl_replacement(char *s)
// {
// 	int		pt;
// 	int		new_len;
// 	char	*new;

// 	pt = -1;
// 	new_len = 0;
// 	while (s[++pt])
// 	{
// 		if (s[pt] != '\\' && s[pt + 1] && s[pt + 1] != '\"')
// 			new_len++;
// 	}
// 	new = (char *)malloc(sizeof(char) * new_len + 1);
// 	pt = -1;
// 	new_len = 0;
// 	while (s[++pt])
// 	{
// 		if (s[pt] == '\\' && s[pt + 1] && s[pt + 1] == '\"')
// 			continue ;
// 		new[new_len++] = s[pt];
// 	}
// 	new[new_len] = '\0';
// 	free(s);
// 	return (new);
// }

// char	*ft_srch_pair_quote(char *s, int c)
// {
// 	int	i;
// 	int	f_i;

// 	i = 0;
// 	f_i = -1;
// 	while (s[i] != 0)
// 	{
// 		if (s[i] == c && s[i - 1] != '\\')
// 		{
// 			f_i = i;
// 			break ;
// 		}
// 		i++;
// 	}
// 	if (c == '\0')
// 		return (&s[i]);
// 	else if (f_i == -1)
// 		return (NULL);
// 	else
// 		return (&s[f_i]);
// }

// char	*ft_dbl_quoteproccessing(char *s, int *add)
// {
// 	char	*next_c;
// 	char	*ret;
// 	int		len;

// 	len = 0;
// 	next_c = ft_srch_pair_quote(&s[1], s[0]);
// 	if (next_c == NULL)
// 	{
// 		ret = NULL;
// 		printf("INCORRECT");
// 	}
// 	else
// 	{
// 		len += next_c - &s[len];
// 		ret = malloc(len + 1);
// 		ft_strncpy(&s[1], ret, len);
// 		ret = ft_dbl_replacement(ret);
// 		ret = ft_dbl_quotes_subsit(ret);
// 		*add = len;
// 	}
// 	return (ret);
// }

// char	*ft_single_quote(char *s, int *add)
// {
// 	char	*next_c;
// 	char	*ret;
// 	int		len;

// 	len = 0;
// 	ret = NULL;
// 	next_c = ft_strchr(&s[1], s[0]);
// 	if (next_c == NULL)
// 		printf("INCORRECT");
// 	else
// 	{
// 		len += next_c - &s[len];
// 		ret = malloc(len + 1);
// 		ft_strncpy(&s[1], ret, len);
// 		*add = len;
// 	}
// 	return (ret);
// }
