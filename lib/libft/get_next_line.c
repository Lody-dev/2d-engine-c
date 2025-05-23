/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <lodyiaremko@proton.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:29:32 by viaremko          #+#    #+#             */
/*   Updated: 2024/12/10 19:14:03 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read_fd(int fd, char *buffer)
{
	char	*ptr;
	char	*data;
	ssize_t	bytes;

	bytes = 1;
	ptr = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (buffer && (!ft_strchr(buffer, '\n') && bytes > 0))
	{
		bytes = read(fd, ptr, BUFFER_SIZE);
		if (bytes == -1)
			return (ft_memclean(ptr), ft_memclean(buffer));
		ptr[bytes] = '\0';
		data = buffer;
		buffer = ft_strjoin(buffer, ptr);
		ft_memclean(data);
	}
	ft_memclean(ptr);
	return (buffer);
}

char	*ft_get_line(char *str)
{
	char	*next_line;
	char	*n_pos;
	size_t	i;

	if (!*str)
		return (NULL);
	n_pos = ft_strchr(str, '\n');
	if (n_pos)
		i = n_pos - str + 1;
	else
		i = ft_strlen(str);
	next_line = malloc((i + 1) * sizeof(char));
	if (!next_line)
		return (NULL);
	ft_memcpy(next_line, str, i);
	next_line[i] = '\0';
	return (next_line);
}

char	*ft_buffer_update(char *buffer)
{
	int		i;
	int		j;
	char	*ptr;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
		return (NULL);
	ptr = malloc(((ft_strlen(buffer) - i) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		ptr[j++] = buffer[i++];
	ptr[j] = '\0';
	return (ptr);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*tmp_buffer;
	char		*line;

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		buffer = malloc(1 * sizeof(char));
		if (!buffer)
			return (free(buffer), NULL);
		buffer[0] = '\0';
	}
	buffer = ft_read_fd(fd, buffer);
	if (!buffer)
		return (NULL);
	tmp_buffer = buffer;
	line = ft_get_line(buffer);
	buffer = ft_buffer_update(buffer);
	free(tmp_buffer);
	return (line);
}
