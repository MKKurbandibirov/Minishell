#include "libft.h"

void	ft_strncpy(char *src, char *direc, int len)
{
	char	*tmp;

	tmp = src;
	if (len)
	{
		while (len - 1 > 0 && *tmp)
		{
			*direc++ = *tmp++;
			len--;
		}
		*direc = '\0';
	}
}