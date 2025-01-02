/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:12:07 by iatopchu          #+#    #+#             */
/*   Updated: 2024/01/13 17:08:38 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *buffer, char *leftover)
{
	int		read_elements;
	char	*temp;

	read_elements = read(fd, buffer, BUFFER_SIZE);
	while (read_elements > 0)
	{
		if (read_elements == -1)
		{
			if (leftover)
				free(leftover);
			leftover = NULL;
			return (NULL);
		}
		buffer[read_elements] = '\0';
		temp = leftover;
		leftover = ft_strjoin(temp, buffer);
		if (temp)
			free (temp);
		temp = NULL;
		if (ft_strchr(leftover, '\n'))
			break ;
		read_elements = read(fd, buffer, BUFFER_SIZE);
	}
	return (leftover);
}

char	*divide_line(char **leftover)
{
	int		i;
	char	*line;
	char	*temp;

	i = 0;
	while ((*leftover)[i] != '\0' && (*leftover)[i] != '\n')
		i++;
	temp = *leftover;
	line = ft_substr(temp, 0, i + 1);
	*leftover = ft_substr(temp, i + 1, ft_strlen(temp));
	if (temp)
		free(temp);
	temp = NULL;
	if (!line)
	{
		if (*leftover)
			free(*leftover);
		*leftover = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*line;
	char		*buffer;

	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || fd < 0)
	{
		if (leftover)
			free(leftover);
		leftover = NULL;
		return (NULL);
	}
	if (!leftover)
		leftover = ft_strdup("\0");
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	leftover = read_line(fd, buffer, leftover);
	if (!leftover)
		return (NULL);
	line = divide_line(&leftover);
	if (buffer)
		free(buffer);
	buffer = NULL;
	return (line);
}
