#include "libft.h"

void	ft_strncpy(char *src, char *direc, int len)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = src;
	if (len)
	{
		while (len - 1 > 0 && *tmp)
		{
			direc[i] = tmp[i];
			i++;
			len--;
		}
		direc[i] = '\0';
	}
}