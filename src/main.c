/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <lodyiaremko@proton.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:35:13 by viaremko          #+#    #+#             */
/*   Updated: 2025/05/10 17:23:25 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/so_long.h"

int32_t	main(int argc, char **argv)
{
	mlx_t				*mlx;
	static t_map		data;
	static t_graphics	graphics;
	static t_wrapper	wrapper;

	data = map_validation(argc, argv);
	mlx = mlx_init((data.width - 1) * 128, data.height * 128, "Game", true);
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
