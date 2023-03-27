/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jciapova <jciapova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:48:35 by jciapova          #+#    #+#             */
/*   Updated: 2023/03/22 19:56:40 by jciapova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"
#include <stddef.h>
#include <fcntl.h>
#include <string.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	int		len;

	i = 0;
	len = 0;
	while (src[len] != '\0')
		len++;
	if (size == 0)
		return (len);
	while (src[i] != '\0' && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	*str;

	i = 0;
	j = 0;
	k = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	if (!s1 || !s2)
		return (0);
	while (s1[i])
		str[k++] = s1[i++];
	while (s2[j])
		str[k++] = s2[j++];
	str[k] = '\0';
	return (str);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (c == '\0')
		return ((char *)(s + i));
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, int len)
{
	int	i;
	char	*sub;

	i = strlen(s);
	if (len > i)
		len = i - start;
	if (start > i)
	{
		len = 0;
		start = i;
	}
	if (i - start < len)
		len = i - start;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (s == NULL)
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}

char	*new_line(char *start)
{
	int	i;
	char	*new_line;

	i = 0;
	if (!start)
		return (0);
	while (start[i] != '\n')
		i++;
	if (start[i] == '\n')
		i++;
	new_line = (char *)malloc(sizeof(char) * i + 1);
	if (!new_line)
		return (NULL);
	i = 0;
	while (start[i] != '\n')
	{
		new_line[i] = start[i];
		i++;
	}
	if (start[i] == '\n')
	{
		new_line[i] = '\n';
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

char	*get_next_line(int fd)
{
	char			*buffer;
	static char		*ret;
	int			read_line;

	read_line = 1;
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (read_line != 0)
	{
		read_line = read(fd, buffer, BUFFER_SIZE);
		buffer[read_line] = '\0';
		ret = ft_strjoin(ret, buffer);
		if (ft_strchr(ret, '\n'))
			break;
	}
	free(buffer);
	buffer = new_line(ret);
	return (buffer);
}

int main()
{
    int     fd, i=0;
    char    *line;
    fd = open("test.txt",O_RDONLY);
    while ((line = get_next_line(fd)))
    {
	printf("%s", line);
    	i++;
    }
    printf("%s", get_next_line(fd));
    return (0);
}