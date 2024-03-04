/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:44:33 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/03/04 16:33:55 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int32_t	main(void)
{
	mlx_t			*mlx;
	t_img			*img;
	t_map			*map;

	img = (t_img *)malloc(sizeof(t_img));
	map = (t_map *)malloc(sizeof(t_map));
	map->filename = "./maps/map.ber";
	map->img = img;
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "solo ng", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	map->mlx = mlx;
	initialize_map_values(map);
	mapping(map);
	render_map(mlx, map, img);
	printf("sasadasd\n");
	render_player(mlx, img, map);
	mlx_key_hook(mlx, move_hook, map);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
