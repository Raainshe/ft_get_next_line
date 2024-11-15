/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:13:24 by rmakoni           #+#    #+#             */
/*   Updated: 2024/11/12 13:39:13 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, ssize_t *bytes_read)
{
	char	*temp;

	temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	*bytes_read = read(fd, temp, BUFFER_SIZE);
	if (*bytes_read == -1)
	{
		free(temp);
		return (NULL);
	}
	temp[*bytes_read] = '\0';
	return (temp);
}

char	*get_my_line(char *line_buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!line_buffer || line_buffer[0] == '\0')
		return (NULL);
	while (line_buffer[i] != '\0' && line_buffer[i] != '\n')
		i++;
	if (line_buffer[i] == '\n')
		line = ft_substr(line_buffer, 0, i + 1);
	else
		line = ft_substr(line_buffer, 0, i);
	return (line);
}

void	update_buffer(char **line_buffer, char *line)
{
	size_t	len;
	char	*new_buffer;

	len = ft_strlen(line);
	new_buffer = ft_substr(*line_buffer, len, ft_strlen(*line_buffer) - len);
	free(*line_buffer);
	*line_buffer = new_buffer;
}

int	get_full_line(int fd, char **line_buffer)
{
	char	*temp;
	char	*old_buffer;
	ssize_t	bytes_read;

	while (1)
	{
		temp = read_file(fd, &bytes_read);
		if (!temp)
			return (0);
		if (*line_buffer)
		{
			old_buffer = *line_buffer;
			*line_buffer = ft_strjoin(old_buffer, temp);
			free(old_buffer);
		}
		else
			*line_buffer = ft_strdup(temp);
		free(temp);
		if (!*line_buffer)
			return (0);
		if (ft_strchr(*line_buffer, '\n') || bytes_read < BUFFER_SIZE)
			break ;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*line_buffer = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!get_full_line(fd, &line_buffer))
	{
		free(line_buffer);
		line_buffer = NULL;
		return (NULL);
	}
	line = get_my_line(line_buffer);
	if (!line)
	{
		free(line_buffer);
		line_buffer = NULL;
		return (NULL);
	}
	update_buffer(&line_buffer, line);
	return (line);
}
// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	i = 1;
// 	// Open the file in read-only mode
// 	fd = open("Test.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	// Read lines using get_next_line until EOF
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("Line %i: %s", i++, line); // Print each line returned
// 		free(line);
// 		// Free the line after printing to avoid memory leaks
// 	}
// 	// Close the file
// 	close(fd);
// 	return (0);
// }
