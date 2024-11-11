/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:04:12 by rmakoni           #+#    #+#             */
/*   Updated: 2024/11/11 19:30:45 by rmakoni          ###   ########.fr       */
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
	int		j;
	char	*new_buffer;

	i = 0;
	if (!line_buffer)
		return (NULL);
	while (line_buffer[i] != '\0' && line_buffer[i] != '\n')
		i++;
	if (!line_buffer[i])
		return (free(line_buffer), NULL);
	i++;
	if (!line_buffer[i])
		return (free(line_buffer), NULL);
	new_buffer = malloc((ft_strlen(&line_buffer[i]) + 1) * sizeof(char));
	if (!new_buffer)
		return (free(line_buffer), NULL);
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
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(line_buffer), free(temp_buffer), NULL);
		temp_buffer[bytes_read] = '\0';
		if (bytes_read == 0)
			break ;
		line_buffer = ft_join_free(line_buffer, temp_buffer);
		if (!line_buffer)
			return (free(temp_buffer), (NULL));
		if (ft_strchr(line_buffer, '\n'))
			break ;
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
		line_buffer[0] = '\0';
	}
	line_buffer = read_file(fd, line_buffer);
	if (!line_buffer)
		return (NULL);
	line = get_my_line(line_buffer);
	if (!line || line_buffer[0] == '\0')
	{
		free(line_buffer);
		line_buffer = NULL;
		return (NULL);
	}
	line_buffer = update_buffer(line_buffer);
	return (line);
}

// char	*get_my_line(char *line_buffer)
// {
// 	int		i;
// 	char	*line;

// 	i = 0;
// 	if (!line_buffer || line_buffer[0] == '\0')
// 		return (NULL);
// 	while (line_buffer[i] != '\0' && line_buffer[i] != '\n')
// 		i++;
// 	if (line_buffer[i] == '\n')
// 		line = ft_substr(line_buffer, 0, i + 1);
// 	else
// 		line = ft_substr(line_buffer, 0, i);
// 	return (line);
// }
// char	*read_file(int fd)
// {
// 	ssize_t	bytes_read;
// 	char	*temp;

// 	temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
// 	if (!temp)
// 		return (NULL);
// 	bytes_read = read(fd, temp, BUFFER_SIZE);
// 	if (bytes_read == -1)
// 	{
// 		free(temp);
// 		return (NULL);
// 	}
// 	temp[bytes_read] = '\0';
// 	return (temp);
// }

// void	update_buffer(char **line_buffer, char *line)
// {
// 	size_t	len;
// 	char	*new_buffer;

// 	len = ft_strlen(line);
// 	new_buffer = ft_substr(*line_buffer, len, ft_strlen(*line_buffer) - len);
// 	free(*line_buffer);
// 	*line_buffer = new_buffer;
// }

// int	get_full_line(int fd, char **line_buffer)
// {
// 	char	*temp;
// 	char	*old_buffer;

// 	if (!*line_buffer)
// 		*line_buffer = ft_strdup("");
// 	while (!ft_strchr(*line_buffer, '\n'))
// 	{
// 		temp = read_file(fd);
// 		if (!temp)
// 		{
// 			if (*line_buffer && **line_buffer != '\0')
// 				return (1);
// 			return (0);
// 		}
// 		if (*line_buffer)
// 		{
// 			old_buffer = *line_buffer;
// 			*line_buffer = ft_strjoin(old_buffer, temp);
// 			free(old_buffer);
// 		}
// 		else
// 		{
// 			*line_buffer = ft_strdup(temp);
// 			free(temp);
// 		}
// 		if (!*line_buffer)
// 			return (0);
// 	}
// 	return (1);
// }

// char	*get_next_line(int fd)
// {
// 	static char	*line_buffer;
// 	char		*line;

// 	line_buffer = NULL;
// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	if (!get_full_line(fd, &line_buffer))
// 	{
// 		free(line_buffer);
// 		line_buffer = NULL;
// 		return (NULL);
// 	}
// 	line = get_my_line(line_buffer);
// 	if (!line)
// 	{
// 		free(line_buffer);
// 		line_buffer = NULL;
// 		return (NULL);
// 	}
// 	update_buffer(&line_buffer, line);
// 	return (line);
// }

// #include <dlfcn.h>
// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// int	main(void)
// {
// 	char	*line;
// 	int		fd;

// 	fd = open("Test.txt", O_RDONLY);
// 	line = malloc(500);
// 	line = get_next_line(fd);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	return (0);
// }
