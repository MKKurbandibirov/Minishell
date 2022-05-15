#include "../../header_files/minishell.h"

void	ft_pars(char *s1, int group, int add_len, int i)
{
	t_parser	prs;
	char		*s;

	ft_initparser(&prs);
	if (ft_validate_pairs(s1) != 0)
	{
		printf("ERR NOT VALID STR! ()");
		return ;
	}
	s = ft_substitution(s1, -1);
	while (s[i])
	{
		while (ft_isspace(s[i]) || s[i] == '(')
			i++;
		if (s[i] && s[i] != ')')
		{
			ft_pushback_p(&prs.head, ft_argv_am(&s[i], &add_len), CMD, group);
			i += (add_len);
		}
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i])
			i += (ft_get_arg(&s[i], &group, &prs, 0) - 1);
		i++;
	}
	ft_clear_parslst(&prs, s);
	if (ft_validator(prs.head) == 0)
		printf("OK\n");
	else
		printf("FUCK\n");
}