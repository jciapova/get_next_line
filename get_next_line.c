/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:48:35 by jciapova          #+#    #+#             */
/*   Updated: 2023/04/15 12:05:48 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"
#include <stddef.h>
#include <fcntl.h>
#include <string.h>

char	*new_line(char *start)
{
	int	i;
	char	*new_line;

	i = 0;
	if (!start)
		return (NULL);
	while (start[i] != '\n' && start[i] != '\0')
		i++;
	if (start[i] == '\n')
		i++;
	new_line = (char *)malloc(sizeof(char) * i + 1);
	if (!new_line)
		return (NULL);
	i = 0;
	while (start[i] != '\n' && start[i] != '\0')
	{
		new_line[i] = start[i];
		i++;
	}
	if (start[i] == '\n')
		new_line[i++] = '\n';
	new_line[i] = '\0';
	free(start);
	return (new_line);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*temp;
	static char	buff[BUFFER_SIZE + 1];
	int		read_line;

	read_line = 1;
	line = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, buff, BUFFER_SIZE);
	while (read_line > 0)
	{
		read_line = read(fd, buff, BUFFER_SIZE);
		buff[read_line] = '\0';
		if (read_line == 0)
			break;
		temp = line;
		line = ft_strjoin(temp, buff);
		free(temp);
		if (ft_strchr(buff, '\n'))
		{
			temp = ft_strchr(line, '\n');
			ft_strlcpy(buff, temp + 1, ft_strlen(temp + 1) + 1);
			line = new_line(line);
			break;
		}
	}
	if (read_line == -1)
	{	
		free (line);
		return (NULL);
	}
	return (line);
}

// int main()
// {
// 	int     fd, i=0;
// 	char    *line;
// 	fd = open("test.txt",O_RDONLY);
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	return (0);
// }
