// Written by Bruh

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../lib/MLX42/include/MLX42/MLX42.h" ///home/viaremko/Documents/so_long/lib/MLX42/include/MLX42
#define WIDTH 1280
#define HEIGHT 720

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	(void)param;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		puts("Move forward");

	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		puts("Move backward");

	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		puts("Move left");

	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		puts("Move right");

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(param);
}

int32_t	main(void)
{
	mlx_t* mlx;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
		return (EXIT_FAILURE);
	mlx_key_hook(mlx, &my_keyhook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
