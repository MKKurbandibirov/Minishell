/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:19:57 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/07/04 17:07:35 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*trim_line(char *rem)
{
	char	*line;
	int		len;

	len = 0;
	if (!rem[0])
		return (NULL);
	while (rem[len] != '\n' && rem[len])
		len++;
	line = malloc((len + 2) * sizeof(char));
	if (!line)
		return (NULL);
	len = 0;
	while (rem[len] != '\n' && rem[len])
	{
		line[len] = rem[len];
		len++;
	}
	if (rem[len] == '\n')
	{
		line[len] = rem[len];
		len++;
	}
	line[len] = '\0';
	return (line);
}

char	*trim_rem(char *rem)
{
	char	*new_rem;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (rem[len] != '\n' && rem[len])
		len++;
	if (!rem[len])
	{
		free(rem);
		return (NULL);
	}
	new_rem = malloc((ft_strlen(rem) - len + 1) * sizeof(char));
	if (!new_rem)
		return (NULL);
	len++;
	while (rem[len])
		new_rem[i++] = rem[len++];
	new_rem[i] = '\0';
	free(rem);
	return (new_rem);
}

char	*read_str(int fd, char *rem)
{
	char	*buf;
	int		end;

	end = 1;
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	while (!govnishe(rem, '\n') && end)
	{
		end = read(fd, buf, BUFFER_SIZE);
		if (end == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[end] = '\0';
		rem = gnl_join(rem, buf);
	}
	free(buf);
	return (rem);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*rem;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	rem = read_str(fd, rem);
	if (!rem)
		return (NULL);
	line = trim_line(rem);
	rem = trim_rem(rem);
	return (line);
}
