#include "libft.h"

void	ft_strncpy(char *src, char *direc, int len)
{
	int		i;
	char	*tmp;

	tmp = src;
	i = 0;
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