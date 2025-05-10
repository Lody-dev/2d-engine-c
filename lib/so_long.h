/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <lodyiaremko@proton.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:35:13 by viaremko          #+#    #+#             */
/*   Updated: 2025/05/10 17:23:25 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SO_LONG_H
# define SO_LONG_H
# include "./MLX42/include/MLX42/MLX42.h"
# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_map
{
	char			**map;
	char			**map_copy;
	int				height;
	int				width;
	int				coins;
	int				player;
	int				exit;
	int				p_x;
	int				p_y;
	int				cur_exit;
	int				cur_coins;
	int				moves;
}					t_map;

typedef struct s_graphics
{
	mlx_texture_t	*textures[5];
	mlx_image_t		*images[5];
}					t_graphics;

typedef struct s_wrapper
{
	t_map			data;
	t_graphics		graphics;
	mlx_t			mlx;
}					t_wrapper;

void				load_textures(t_graphics *textures);
void				ttoi(mlx_t *mlx, t_graphics *graphics);
void				render_map(mlx_t *mlx, t_graphics graphics, t_map data);
void				delete_old_images(mlx_t *mlx, t_graphics *graphics);
void				free_everything(mlx_t *mlx, t_graphics *graphics,
						t_map *data);
t_map				map_read_check(t_map m, char *name);
int					map_init(t_map *data);
int					get_map(char **map, char *name);
int					get_map_copy(t_map *data);
void				free_map(t_map *data, int flag);
int					wall_check(t_map data);
int					extention_check(int argc, char **argv);
int					content_check(t_map *data);
void				get_player_position(t_map *data);
int					dfs(t_map *data, int x, int y);
t_map				map_validation(int argc, char **argv);
void				move_to(t_map *cords, int s_y, int s_x);
void				movement(mlx_key_data_t keydata, void *param);

#endif
