#include "../lib/MLX42/include/MLX42/MLX42.h" ///home/viaremko/Documents/so_long/lib/MLX42/include/MLX42
#include "../lib/so_long.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define T_W 64
#define T_H 64

void load_textures(t_graphics *textures)
{
	textures->textures[0] = mlx_load_png("./textures/random.png");
	textures->textures[1] = mlx_load_png("./textures/tile.png");
	textures->textures[2] = mlx_load_png("./textures/coin.png");
	textures->textures[3] = mlx_load_png("./textures/player.png");
	textures->textures[4] = mlx_load_png("./textures/exit1.png");
	ft_printf("Textures loaded\n");
}

void ttoi(mlx_t *mlx, t_graphics *graphics)
{
	graphics->images[0] = mlx_texture_to_image(mlx, graphics->textures[0]);
	graphics->images[1] = mlx_texture_to_image(mlx, graphics->textures[1]);
	graphics->images[2] = mlx_texture_to_image(mlx, graphics->textures[2]);
	graphics->images[3] = mlx_texture_to_image(mlx, graphics->textures[3]);
	graphics->images[4] = mlx_texture_to_image(mlx, graphics->textures[4]);
	ft_printf("Images loaded\n");
}

void render_map(mlx_t *mlx, t_graphics graphics, map data)
{
	int y;
	int x;
	
	y = -1;
	while(++y < data.height)
	{
		x = -1;
		while(++x < data.width)
		{
			if(data.map[y][x] == '1')
				mlx_image_to_window(mlx, graphics.images[0], x * 64, y * 64);
			if(data.map[y][x] == '0')
				mlx_image_to_window(mlx, graphics.images[1], x * 64, y * 64);
			if(data.map[y][x] == 'C')
				mlx_image_to_window(mlx, graphics.images[2], x * 64, y * 64);
			if(data.map[y][x] == 'P')
				mlx_image_to_window(mlx, graphics.images[3], x * 64, y * 64);
			if(data.map[y][x] == 'E')
				mlx_image_to_window(mlx, graphics.images[4], x * 64, y * 64);
		}
	}	
}

void free_everything(mlx_t *mlx, t_graphics *graphics, map *data)
{
	int i;

	i = -1;
	while(++i <= 4)
	{
		mlx_delete_texture(graphics->textures[i]);
		mlx_delete_image(mlx, graphics->images[i]);
	}
	i = -1;
	while(++i < data->height)
		free(data->map[i]);
	free(data->map);
}

void movement(mlx_key_data_t keydata, void* param)
{
	t_wrapper *wrapper = (t_wrapper*)param;
	map *cords = &wrapper->data;	
	t_graphics *graphics = &wrapper->graphics;
	mlx_t *mlx = &wrapper->mlx;
	
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		if (cords->map[cords->p_y + 1][cords->p_x] != '1')
		{
			cords->map[cords->p_y][cords->p_x] = '0';
			cords->map[cords->p_y + 1][cords->p_x] = 'P';
			cords->p_y++;
		}
		ft_printf("Cords: Y->%d X->%d\n", cords->p_y, cords->p_x);
		render_map(mlx, *graphics, *cords);
	}
	
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	{
		if (cords->map[cords->p_y][cords->p_x - 1] != '1')
		{
			cords->map[cords->p_y][cords->p_x] = '0';
			cords->map[cords->p_y][cords->p_x - 1] = 'P';
			cords->p_x--;
		}
		ft_printf("Cords: Y->%d X->%d\n", cords->p_y, cords->p_x);
		render_map(mlx, *graphics, *cords);
	}
	
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	{
		if (cords->map[cords->p_y - 1][cords->p_x] != '1')
		{
			cords->map[cords->p_y][cords->p_x] = '0';
			cords->map[cords->p_y - 1][cords->p_x] = 'P';
			cords->p_y--;
		}
		ft_printf("Cords: Y->%d X->%d\n", cords->p_y, cords->p_x);
		render_map(mlx, *graphics, *cords);
	}
	
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	{
		if (cords->map[cords->p_y][cords->p_x + 1] != '1')
		{
			cords->map[cords->p_y][cords->p_x] = '0';
			cords->map[cords->p_y][cords->p_x + 1] = 'P';
			cords->p_x++;
		}
		ft_printf("Cords: Y->%d X->%d\n", cords->p_y, cords->p_x);
		render_map(mlx, *graphics, *cords);
	}
}

int32_t	main(int argc, char **argv)
{
	static	map	data;
	static	t_graphics	graphics;	
	static 	t_wrapper	wrapper;	
	data = map_validation(argc, argv);
	mlx_t* mlx = mlx_init((data.width-1) * 64, data.height * 64, "Name", true);
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
		

	free_everything(mlx, &graphics, &data);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
