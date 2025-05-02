/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <lodyiaremko@proton.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:29:32 by viaremko          #+#    #+#             */
/*   Updated: 2025/05/02 16:14:42 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../lib/libft/libft.h"
#include "../lib/so_long.h"

int	main(int argc, char **argv)
{
	static map	dimensions;

	if (extention_check(argc, argv) == -1)
		return (1);
	dimensions = map_read_check(dimensions, argv[1]);
	if (map_init(&dimensions) == -1)
		return (2);
	if (get_map(dimensions.map, argv[1]) == -1)
		return (3);
	if (wall_check(dimensions) == -1)
		return (4);
	if (content_check(&dimensions) == -1)
		return (5);
	get_player_position(&dimensions);
	if (get_map_copy(&dimensions) == -1)
		return (6);
	if (dfs(&dimensions, dimensions.p_x, dimensions.p_y) == -1)
		return (7);
	free_copy(&dimensions);
	ft_printf("Map valid!\n");
	return (0);
}
