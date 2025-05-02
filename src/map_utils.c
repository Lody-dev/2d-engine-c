/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <lodyiaremko@proton.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:29:32 by viaremko          #+#    #+#             */
/*   Updated: 2025/05/02 18:34:05 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../lib/libft/libft.h"
#include "../lib/so_long.h"

map	map_read_check(map m, char *name)
{
	int		fd;
	char	*line;

	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Can't find \"%s\"\n", name);
		exit(-1);
	}
	else
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			if (m.width < (int)ft_strlen(line))
				m.width = ft_strlen(line);
			m.height++;
			free(line);
			line = get_next_line(fd);
		}
		free(line);
	}
	close(fd);
	ft_printf("H:%d\nW:%d\n", m.height, m.width);
	return (m);
}

int	map_init(map *data)
{
	data->map = calloc(1, data->height * sizeof(char *));
	if (data->map == NULL)
		return (-1);
	data->map_copy = calloc(1, data->height * sizeof(char *));
	if (data->map_copy == NULL)
		return (-1);
	return (1);
}

int	get_map(char **map, char *name)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(name, O_RDONLY);
	i = 0;
	if (fd == -1)
	{
		ft_printf("Can't find %s\n", name);
		return (-1);
	}
	else
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			map[i] = line;
			i++;
			line = get_next_line(fd);
		}
	}
	close(fd);
	ft_printf("Map stored succesfully!\n");
	return (1);
}

int	get_map_copy(map *data)
{
	int	i;

	i = -1;
	while (++i < data->height)
		data->map_copy[i] = ft_strdup(data->map[i]);
	return (1);
}

void	free_map(map *data, int flag)
{
	int	i;

	i = -1;
	while (++i < data->height)
		free(data->map_copy[i]);
	free(data->map_copy);
	if (flag == -1)
	{
		i = -1;
		while (++i < data->height)
			free(data->map[i]);
		free(data->map);
		ft_printf("Error\n");
		exit(1);
	}
}
