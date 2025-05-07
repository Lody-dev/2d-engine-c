#ifndef SO_LONG_H
# define SO_LONG_H

typedef struct
{
	char	**map;
	char	**map_copy;
	int		height;
	int		width;
	int		coins;
	int		player;
	int		exit;
	int		p_x;
	int		p_y;
	int		cur_exit;
	int		cur_coins;
}map;

typedef struct
{
	mlx_texture_t	*textures[5];
	mlx_image_t	*images[5];
}t_graphics;

# include "../src/map_utils.c"
# include "../src/map_utils_2.c"
# include "../src/map_validation.c"

#endif
