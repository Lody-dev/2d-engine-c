/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asierra- <asierra-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:35:13 by asierra-          #+#    #+#             */
/*   Updated: 2025/05/10 17:23:25 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/so_long.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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

void	render_map(mlx_t *mlx, t_graphics graphics, map data)
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

void	free_everything(mlx_t *mlx, t_graphics *graphics, map *data)
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

void	move_to(map *cords, int s_y, int s_x)
{
	int	new_x;
	int	new_y;

	new_y = cords->p_y + s_y;
	new_x = cords->p_x + s_x;
	if (cords->map[new_y][new_x] == 'C')
		cords->cur_coins--;
	if (cords->map[new_y][new_x] == 'E' && cords->cur_coins == 0)
		cords->cur_exit--;
	if (cords->map[new_y][new_x] != '1' && (cords->map[new_y][new_x] != 'E'
			&& cords->coins != '0'))
	{
		cords->map[cords->p_y][cords->p_x] = '0';
		cords->map[new_y][new_x] = 'P';
		cords->p_y = new_y;
		cords->p_x = new_x;
		cords->moves++;
		ft_printf("Moves taken: %d\n", cords->moves);
	}
}

void	movement(mlx_key_data_t keydata, void *param)
{
	t_wrapper	*wrapper;

	wrapper = (t_wrapper *)param;
	if (wrapper->data.cur_coins == 0 && wrapper->data.cur_exit == 0)
	{
		free_everything(&wrapper->mlx, &wrapper->graphics, &wrapper->data);
		return mlx_close_window(&wrapper->mlx);
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(&wrapper->mlx);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move_to(&wrapper->data, 1, 0);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move_to(&wrapper->data, 0, -1);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		move_to(&wrapper->data, -1, 0);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move_to(&wrapper->data, 0, 1);
	delete_old_images(&wrapper->mlx, &wrapper->graphics);
	ttoi(&wrapper->mlx, &wrapper->graphics);
	render_map(&wrapper->mlx, wrapper->graphics, wrapper->data);
}

int32_t	main(int argc, char **argv)
{
	mlx_t				*mlx;
	static map			data;
	static t_graphics	graphics;
	static t_wrapper	wrapper;

	data = map_validation(argc, argv);
	mlx = mlx_init((data.width - 1) * 64, data.height * 64, "Game", true);
	if (!mlx)
		exit(1);
	load_textures(&graphics);
	ttoi(mlx, &graphics);
	render_map(mlx, graphics, data);
	wrapper.data = data;
	wrapper.graphics = graphics;
	wrapper.mlx = *mlx;
	mlx_key_hook(mlx, &movement, &wrapper);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
