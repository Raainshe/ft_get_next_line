/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:04:12 by rmakoni           #+#    #+#             */
/*   Updated: 2024/10/31 11:00:01 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_join_free(char *line_buffer, char *temp_buffer)
{
	char	*new_buffer;

	new_buffer = ft_strjoin(line_buffer, temp_buffer);
	if (!new_buffer)
	{
		free(line_buffer);
		return (NULL);
	}
	free(line_buffer);
	return (new_buffer);
}

char	*get_line(char *line_buffer)
{
	int		i;
	char	*line;

	i = 0;
	while (line_buffer[i] != '\n' || line_buffer[i] != '\0')
		i++;
	line = ft_calloc((size_t)i + 1, 1);
	if (!line)
		return (NULL);
	line = ft_substr(line_buffer, 0, i);
	if (line_buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*append_line(int fd)
{
	char	*line_buffer;
	int		bytes_read;
	char	*temp_buffer;

	temp_buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!temp_buffer)
		return (NULL);
	line_buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!line_buffer)
	{
		free(temp_buffer);
		return (NULL);
	}
	while ((bytes_read = read(fd, temp_buffer, BUFFER_SIZE)) > 0)
	{
		temp_buffer[bytes_read] = '\0';
		line_buffer = ft_join_free(line_buffer, temp_buffer);
		if (ft_strchr(temp_buffer, '\n'))
			break ;
	}
	free(temp_buffer);
	if (bytes_read == -1)
	{
		free(temp_buffer);
		return (NULL);
	}
	return (line_buffer);
}

char	*get_next_line(int fd)
{
	char	*line;
	char	*line_buffer;

	line_buffer = NULL;
	if (BUFFER_SIZE <= 0 || fd <= 0)
		return (NULL);
	line = append_line(fd);
	if (!line)
		return (NULL);
	line = get_line(line_buffer);
	free(line_buffer);
	return (line);
}
