/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:44:33 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/03/21 16:35:15 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int32_t	main(int argc, char **argv)
{
	mlx_t			*mlx;
	t_img			*img;
	t_map			*map;

	img = (t_img *)malloc(sizeof(t_img));
	map = (t_map *)malloc(sizeof(t_map));
	if (argc != 2)
	{
		puts("Error\nInvalid number of arguments");
		return (EXIT_FAILURE);
	}
	map->filename = argv[1];
	map->img = img;
	mlx = mlx_init(WIDTH, HEIGHT, "solo ng", true);
	if (!mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	map->mlx = mlx;
	//map_validation(map);
	initialize_map_values(map);
	mapping(map);
	render_map(mlx, map, img);
	printf("sasadasd\n");
	render_player(mlx, img, map);
	mlx_key_hook(mlx, move_hook, map);
	// TODO: hook for window size change
	mlx_resize_hook(mlx, resize_hook, map);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
