/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:49:19 by rmakoni           #+#    #+#             */
/*   Updated: 2024/11/08 18:25:59 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *str)
{
	size_t	s_len;
	size_t	i;
	char	*dup;

	s_len = ft_strlen((char *)str);
	dup = malloc(s_len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

//Is used to locate the first occurrence of a specified character in a string.
char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	s_len;

	s_len = ft_strlen((char *)s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (start + len > s_len)
		len = s_len - start;
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*joined;

	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	i = 0;
	joined = malloc(s1_len + s2_len + 1);
	if (!joined)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		joined[i] = (char)s1[i];
		i++;
	}
	while (s2[i - s1_len])
	{
		joined[i] = (char)s2[i - s1_len];
		i++;
	}
	free((char *)s2);
	joined[i] = '\0';
	return (joined);
}
