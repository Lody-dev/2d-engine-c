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
