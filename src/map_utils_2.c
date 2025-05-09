/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <lodyiaremko@proton.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:29:32 by viaremko          #+#    #+#             */
/*   Updated: 2025/05/09 20:25:50 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../lib/libft/libft.h"
#include "../lib/so_long.h"

int	wall_check(map data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data.width - 1)
	{
		if ((data.map[0][i] != '1') || (data.map[data.height - 1][i] != '1'))
		{
			ft_printf("Wall check KO!\n");
			return (-1);
		}
		i++;
	}
	while (j < data.height - 1)
	{
		if (data.map[j][0] != '1' || data.map[j][data.width - 2] != '1')
		{
			ft_printf("Wall check KO!\n");
			return (-1);
		}
		j++;
	}
	ft_printf("Wall check OK!\n");
	return (1);
}

int	extention_check(int argc, char **argv)
{
	int	count;

	if (argc != 2)
	{
		ft_printf("Usage: ./Game map.ber\n");
		return (-1);
	}
	count = strlen(argv[1]);
	if (ft_strncmp(&argv[1][count - 4], ".ber", 4) == 0)
	{
		ft_printf("Correct extention\n");
		return (0);
	}
	printf("Incorrect extention\n");
	return (-1);
}

int	content_check(map *data)
{
	int	i;
	int	j;

	i = 0;
	while (++i < (data->height - 1))
	{
		j = 0;
		while (++j < (data->width - 2))
		{
			if (data->map[i][j] == '0' || data->map[i][j] == '1')
				continue ;
			else if (data->map[i][j] == 'C')
				data->coins = data->coins + 1;
			else if (data->map[i][j] == 'P')
				data->player = data->player + 1;
			else if (data->map[i][j] == 'E')
				data->exit = data->exit + 1;
			else
				return (-1);
		}
	}
	if (data->exit > 1 || data->player > 1 || data->coins < 1)
		return (-1);
	return (0);
}

void	get_player_position(map *data)
{
	int	i;
	int	j;

	i = 0;
	while (++i < (data->height - 1))
	{
		j = 0;
		while (++j < (data->width - 2))
		{
			if (data->map[i][j] == 'P')
			{
				data->p_x = j;
				data->p_y = i;
			}
		}
	}
	ft_printf("Player position: X -> %d   Y -> %d\n", data->p_x, data->p_y);
}

int	dfs(map *data, int x, int y)
{
	if (x < 0 || y < 0 || data->map_copy[y] == 0 || data->map_copy[y][x] == 0)
		return (-1);
	if (data->map_copy[y][x] == 'C')
		data->cur_coins++;
	if (data->map_copy[y][x] == 'E')
		data->cur_exit++;
	if (data->map_copy[y][x] == '1')
		return (-1);
	else
	{
		data->map_copy[y][x] = '1';
		dfs(data, x + 1, y);
		dfs(data, x - 1, y);
		dfs(data, x, y + 1);
		dfs(data, x, y - 1);
	}
	if (data->cur_coins == data->coins && data->cur_exit == 1)
		return (0);
	return (-1);
}
