/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:04:12 by rmakoni           #+#    #+#             */
/*   Updated: 2024/11/04 11:59:03 by rmakoni          ###   ########.fr       */
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

char	*get_my_line(char *line_buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!line_buffer || !line_buffer[0])
		return (NULL);
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == '\n')
		i++;
	line = ft_substr(line_buffer, 0, i);
	if (!line)
		return (NULL);
	return (line);
}

char	*update_buffer(char *line_buffer)
{
	int		i;
	char	*new_buffer;
	int		j;

	i = 0;
	if (!line_buffer)
		return (NULL);
	while (line_buffer[i] != '\0' && line_buffer[i] != '\n')
		i++;
	if (line_buffer[i] == '\n')
		i++;
	if (!line_buffer[i])
		return (free(line_buffer), NULL);
	new_buffer = malloc((ft_strlen(&line_buffer[i]) + 1) * sizeof(char));
	if (!new_buffer)
	{
		free(line_buffer);
		return (NULL);
	}
	j = 0;
	while (line_buffer[i])
		new_buffer[j++] = line_buffer[i++];
	new_buffer[j] = '\0';
	return (free(line_buffer), new_buffer);
}

char	*read_file(int fd, char *line_buffer)
{
	char	*temp_buffer;
	int		bytes_read;

	if (!line_buffer)
		return (NULL);
	temp_buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp_buffer)
		return (free(temp_buffer), NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(line_buffer, '\n'))
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(temp_buffer), free(line_buffer), NULL);
		if (bytes_read == 0)
			break ;
		temp_buffer[bytes_read] = '\0';
		line_buffer = ft_join_free(line_buffer, temp_buffer);
		if (!line_buffer)
		{
			free(temp_buffer);
			return (NULL);
		}
	}
	return (free(temp_buffer), line_buffer);
}

char	*get_next_line(int fd)
{
	static char	*line_buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!line_buffer)
	{
		line_buffer = malloc(1 * sizeof(char));
		if (!line_buffer)
			return (NULL);
	}
	line_buffer = read_file(fd, line_buffer);
	if (!line_buffer)
		return (NULL);
	line = get_my_line(line_buffer);
	line_buffer = update_buffer(line_buffer);
	return (line);
}
