/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:03:53 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/04/30 13:58:39 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_player(mlx_t *mlx, t_img *img, t_map *map)
{
	mlx_delete_image(mlx, img->img_pl);
	if (map->pl_pos == 1)
		img->img_pl = mlx_texture_to_image(mlx, img->txt_pl_left);
	else if (map->pl_pos == 2)
		img->img_pl = mlx_texture_to_image(mlx, img->txt_pl_collect);
	else
		img->img_pl = mlx_texture_to_image(mlx, img->txt_pl);
	mlx_resize_image(img->img_pl, map->tile_sq / 2, map->tile_sq);
	mlx_image_to_window(mlx, img->img_pl, \
		(map->pl_x * map->tile_sq), map->pl_y * map->tile_sq);
}

void	render_player_and_exit(mlx_t *mlx, t_map *map, t_img *img)
{
	if (map->grid[map->y][map->x] == 'P')
	{
		if (!map->pl_x && !map->pl_y)
		{
			map->pl_x = map->x;
			map->pl_y = map->y;
		}
		render_player(mlx, img, map);
	}
	if (map->grid[map->y][map->x] == 'E')
	{
		mlx_image_to_window(mlx, img->img_exit, \
		map->x * map->tile_sq, map->y * map->tile_sq);
	}
}

void	preload_images(mlx_t *mlx, t_img *img, t_map *map)
{
	map_sizing(map);
	img->txt_free = mlx_load_png("./assets/floor_tile.png");
	img->txt_exit = mlx_load_png("./assets/exit.png");
	img->txt_wall = mlx_load_png("./assets/wall.png");
	img->txt_col = mlx_load_png("./assets/book.png");
	img->txt_pl = mlx_load_png("assets/monky_right.png");
	img->txt_pl_left = mlx_load_png("assets/monky_left.png");
	img->txt_pl_collect = mlx_load_png("assets/anim1.png");
	if (img->txt_free == NULL || img->txt_exit == NULL || \
	img->txt_wall == NULL || img->txt_col == NULL || img->txt_pl == NULL \
	|| img->txt_pl_left == NULL || img->txt_pl_collect == NULL)
	{
		exit_with_error(map, "Error\nFailed to load textures\n");
	}
	img->img_free = mlx_texture_to_image(mlx, img->txt_free);
	img->img_exit = mlx_texture_to_image(mlx, img->txt_exit);
	img->img_wall = mlx_texture_to_image(mlx, img->txt_wall);
	img->img_col = mlx_texture_to_image(mlx, img->txt_col);
	img->img_pl = mlx_texture_to_image(mlx, img->txt_pl);
	mlx_resize_image(img->img_free, map->tile_sq, map->tile_sq);
	mlx_resize_image(img->img_exit, map->tile_sq, map->tile_sq);
	mlx_resize_image(img->img_wall, map->tile_sq, map->tile_sq);
	mlx_resize_image(img->img_col, (map->tile_sq / 2), map->tile_sq / 2);
	mlx_resize_image(img->img_pl, map->tile_sq / 2, map->tile_sq);
}

void	renders(t_map *map, t_img *img, mlx_t *mlx)
{
	mlx_image_to_window(mlx, img->img_free, \
	map->x * map->tile_sq, map->y * map->tile_sq);
	if (map->grid[map->y][map->x] == '1')
	{
		mlx_image_to_window(mlx, img->img_wall, \
		map->x * map->tile_sq, map->y * map->tile_sq);
	}
	else if (map->grid[map->y][map->x] == 'C')
	{
		mlx_image_to_window(mlx, img->img_col, \
		map->x * map->tile_sq, map->y * map->tile_sq);
	}
	else
		render_player_and_exit(mlx, map, img);
}

int	render_map(mlx_t *mlx, t_map *map, t_img *img)
{
	map->x = 0;
	map->y = 0;
	map_sizing(map);
	if (!img->img_pl)
		preload_images(mlx, img, map);
	while (map->y < map->line_count)
	{
		if (!img->img_free || !img->img_exit || !img->img_wall || !img->img_col)
		{
			mlx_close_window(mlx);
			ft_printf(mlx_strerror(mlx_errno));
			return (EXIT_FAILURE);
		}
		while (map->x < map->line_length - 1)
		{
			renders(map, img, mlx);
			map->x++;
		}
		map->y++;
		map->x = 0;
	}
	return (0);
}
