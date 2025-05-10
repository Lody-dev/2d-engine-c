/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <lodyiaremko@proton.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:29:32 by viaremko          #+#    #+#             */
/*   Updated: 2025/05/10 17:50:19 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../lib/libft/libft.h"
#include "../lib/so_long.h"

t_map	map_validation(int argc, char **argv)
{
	static t_map	data;

	if (extention_check(argc, argv) == -1)
		exit(1);
	data = map_read_check(data, argv[1]);
	if (map_init(&data) == -1)
		free_map(&data, -1);
	if (get_map(data.map, argv[1]) == -1)
		free_map(&data, -1);
	if (wall_check(data) == -1)
		free_map(&data, -1);
	if (content_check(&data) == -1)
		free_map(&data, -2);
	get_player_position(&data);
	if (get_map_copy(&data) == -1)
		free_map(&data, -1);
	if (dfs(&data, data.p_x, data.p_y) == -1)
	{
		ft_printf("Imposible to win!\n");
		free_map(&data, -1);
	}
	free_map(&data, 0);
	return (data);
}
