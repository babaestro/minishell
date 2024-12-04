/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:52:06 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/06/04 18:28:00 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_current_line(char *line_limit)
{
	int		i;
	char	*str;

	i = 0;
	if (!line_limit[i])
		return (NULL);
	while (line_limit[i] && line_limit[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (line_limit[i] && line_limit[i] != '\n')
	{
		str[i] = line_limit[i];
		i++;
	}
	if (line_limit[i] == '\n')
	{
		str[i] = line_limit[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_new_line_limit(char *line_limit)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (line_limit[i] && line_limit[i] != '\n')
		i++;
	if (!line_limit[i])
	{
		free(line_limit);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(line_limit) - i + 1));
	if (!str)
	{
		free(str);
		return (NULL);
	}
	i++;
	j = 0;
	while (line_limit[i])
		str[j++] = line_limit[i++];
	str[j] = '\0';
	free(line_limit);
	return (str);
}

char	*ft_read_til_limit(int fd, char *line_limit)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr(line_limit, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		line_limit = ft_strjoin(line_limit, buff);
	}
	free(buff);
	return (line_limit);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*line_limit[MAXFD];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line_limit[fd] = ft_read_til_limit(fd, line_limit[fd]);
	if (!line_limit[fd])
		return (NULL);
	line = ft_get_current_line(line_limit[fd]);
	line_limit[fd] = ft_new_line_limit(line_limit[fd]);
	return (line);
}
