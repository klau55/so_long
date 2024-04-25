/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:44:33 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/04/25 19:59:54 by nkarpilo         ###   ########.fr       */
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
	map->name_length = ft_strlen(map->filename);
	if (map->filename == NULL || \
	ft_strncmp(&map->filename[map->name_length - 4], ".ber", 4))
	{
		ft_printf("Error\n Check map entry\n");
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
	if (mlx)
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
	map_validation(map);
	ft_printf("map->line_count: %d\n", map->line_count);
	ft_printf("map->line_length: %d\n", map->line_length);
	// CHECK LINE COUNT ARGUMENT
	// ??????????????????????????
	mlx = mlx_init(TILE_SIZE * (map->line_length - 1) \
	, TILE_SIZE * map->line_count, "SO LONG", true);
	map->mlx = mlx;
	if (initialization(mlx, map, img) == EXIT_FAILURE)
		return (end(map, img, mlx));
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_key_hook(mlx, move_hook, map);
	mlx_loop(mlx);
	end(map, img, mlx);
	return (EXIT_SUCCESS);
}
