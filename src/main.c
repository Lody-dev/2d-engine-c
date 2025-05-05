#include "../lib/MLX42/include/MLX42/MLX42.h" ///home/viaremko/Documents/so_long/lib/MLX42/include/MLX42
#include "../lib/so_long.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define T_w 64
#define T_H 64

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int32_t	main(int argc, char **argv)
{
	static map	data;
	textures_t	*textures;	
	textures = malloc(sizeof(textures_t));

	data = map_validation(argc, argv);
	mlx_t* mlx = mlx_init(data.width * 64, data.height * 64, "Name", true);
	if (!mlx)
        	error();
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
