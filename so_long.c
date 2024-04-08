/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:44:33 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/04/08 17:51:53 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	initialization(mlx_t *mlx, t_map *map, t_img *img)
{
	if (!mlx)
	{
		ft_printf(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	initialize_map_values(map);
	mapping(map);
	render_map(mlx, map, img);
	return (0);
}

int	end(t_map *map, t_img *img, mlx_t *mlx)
{
	free_grid(map, map->grid);
	free(map);
	free(img);
	mlx_terminate(mlx);
	return (1);
}

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
		return (end(map, img, NULL));
	}
	map->filename = argv[1];
	map->img = img;
	mlx = mlx_init(WIDTH, HEIGHT, "solo ng", true);
	map->mlx = mlx;
	if (initialization(mlx, map, img) == EXIT_FAILURE)
		return (end(map, img, mlx));
	mlx_key_hook(mlx, move_hook, map);
	mlx_resize_hook(mlx, resize_hook, map);
	mlx_loop(mlx);
	end(map, img, mlx);
	return (EXIT_SUCCESS);
}
