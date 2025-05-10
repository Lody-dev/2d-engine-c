/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <lodyiaremko@proton.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:35:13 by viaremko          #+#    #+#             */
/*   Updated: 2025/05/10 17:23:25 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/so_long.h"

void	load_textures(t_graphics *textures)
{
	textures->textures[0] = mlx_load_png("./textures/random.png");
	textures->textures[1] = mlx_load_png("./textures/tile.png");
	textures->textures[2] = mlx_load_png("./textures/coin.png");
	textures->textures[3] = mlx_load_png("./textures/player.png");
	textures->textures[4] = mlx_load_png("./textures/exit1.png");
}

void	ttoi(mlx_t *mlx, t_graphics *graphics)
{
	graphics->images[0] = mlx_texture_to_image(mlx, graphics->textures[0]);
	graphics->images[1] = mlx_texture_to_image(mlx, graphics->textures[1]);
	graphics->images[2] = mlx_texture_to_image(mlx, graphics->textures[2]);
	graphics->images[3] = mlx_texture_to_image(mlx, graphics->textures[3]);
	graphics->images[4] = mlx_texture_to_image(mlx, graphics->textures[4]);
}

void	render_map(mlx_t *mlx, t_graphics graphics, t_map data)
{
	int	y;
	int	x;

	y = -1;
	while (++y < data.height)
	{
		x = -1;
		while (++x < data.width)
		{
			if (data.map[y][x] == '1')
				mlx_image_to_window(mlx, graphics.images[0], x * 64, y * 64);
			if (data.map[y][x] == '0')
				mlx_image_to_window(mlx, graphics.images[1], x * 64, y * 64);
			if (data.map[y][x] == 'C')
				mlx_image_to_window(mlx, graphics.images[2], x * 64, y * 64);
			if (data.map[y][x] == 'P')
				mlx_image_to_window(mlx, graphics.images[3], x * 64, y * 64);
			if (data.map[y][x] == 'E')
				mlx_image_to_window(mlx, graphics.images[4], x * 64, y * 64);
		}
	}
}

void	delete_old_images(mlx_t *mlx, t_graphics *graphics)
{
	mlx_delete_image(mlx, graphics->images[0]);
	mlx_delete_image(mlx, graphics->images[1]);
	mlx_delete_image(mlx, graphics->images[2]);
	mlx_delete_image(mlx, graphics->images[3]);
	mlx_delete_image(mlx, graphics->images[4]);
}

void	free_everything(mlx_t *mlx, t_graphics *graphics, t_map *data)
{
	int	i;

	i = -1;
	while (++i <= 4)
	{
		mlx_delete_texture(graphics->textures[i]);
		mlx_delete_image(mlx, graphics->images[i]);
	}
	i = -1;
	while (++i < data->height)
		free(data->map[i]);
	free(data->map);
}
