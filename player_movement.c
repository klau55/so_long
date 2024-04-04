/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:04:18 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/04/04 18:56:56 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	collectible_animation(mlx_t *mlx, t_map *map, t_img *img)
{
	mlx_delete_image(mlx, img->img_pl);
	img->txt_pl = mlx_load_png("assets/anim1.png");
	img->img_pl = mlx_texture_to_image(mlx, img->txt_pl);
	mlx_resize_image(img->img_pl, map->tile_sq / 2, map->tile_sq);
	mlx_image_to_window(mlx, img->img_pl, \
		(map->pl_x * map->tile_sq), map->pl_y * map->tile_sq);
}

void	completion_checker(mlx_t *mlx, t_map *map, t_img *img)
{
	if (map->grid[map->pl_y][map->pl_x] == 'C')
	{
		collectible_animation(mlx, map, img);
		mlx_delete_image(mlx, img->img_pl);
		mlx_image_to_window(mlx, img->img_free, \
			map->pl_x * map->tile_sq, map->pl_y * map->tile_sq);
		img->img_pl = mlx_texture_to_image(mlx, img->txt_pl);
		mlx_resize_image(img->img_pl, map->tile_sq / 2, map->tile_sq);
		mlx_image_to_window(mlx, img->img_pl, \
			map->pl_x * map->tile_sq, map->pl_y * map->tile_sq);
		puts("collectible found!\n");
		map->col_col++;
		map->grid[map->pl_y][map->pl_x] = '0';
	}
	if (map->grid[map->pl_y][map->pl_x] == 'E')
	{
		if (map->col_col == map->col_c)
		{
			puts("Yay! books collected and exit found!\n");
			mlx_terminate(mlx);
			free_grid(map, map->grid);
			exit(EXIT_SUCCESS);
		}
		else
			puts("collect all books before exit\n");
	}
}

void	player_rotate(mlx_t *mlx, t_map *map, t_img *img, char c)
{
	if (c == 'a')
	{
		mlx_delete_image(mlx, img->img_pl);
		img->txt_pl = mlx_load_png("assets/monky_left.png");
		img->img_pl = mlx_texture_to_image(mlx, img->txt_pl);
		mlx_resize_image(img->img_pl, map->tile_sq / 2, map->tile_sq);
		mlx_image_to_window(mlx, img->img_pl, \
			(map->pl_x * map->tile_sq), map->pl_y * map->tile_sq);
	}
	if (c == 'd' || c == 'w' || c == 's')
	{
		mlx_delete_image(mlx, img->img_pl);
		img->txt_pl = mlx_load_png("assets/monky_right.png");
		img->img_pl = mlx_texture_to_image(mlx, img->txt_pl);
		mlx_resize_image(img->img_pl, map->tile_sq / 2, map->tile_sq);
		mlx_image_to_window(mlx, img->img_pl, \
			(map->pl_x * map->tile_sq), map->pl_y * map->tile_sq);
	}
	map->moves++;
	puts("Number of movements: ");
	putnbr(map->moves);
	puts("\n");
}

void	player_moving(mlx_t *mlx, t_map *map, t_img *img, char c)
{
	if ((c == 'a') && (map->grid[map->pl_y][map->pl_x - 1] != '1'))
	{
		player_rotate(mlx, map, img, c);
		img->img_pl->instances[0].x -= map->tile_sq;
		map->pl_x--;
	}
	else if ((c == 'd') && (map->grid[map->pl_y][map->pl_x + 1] != '1'))
	{
		player_rotate(mlx, map, img, c);
		img->img_pl->instances[0].x += map->tile_sq;
		map->pl_x++;
	}
	else if ((c == 'w') && (map->grid[map->pl_y - 1][map->pl_x] != '1'))
	{
		player_rotate(mlx, map, img, c);
		img->img_pl->instances[0].y -= map->tile_sq;
		map->pl_y--;
	}
	else if ((c == 's') && (map->grid[map->pl_y + 1][map->pl_x] != '1'))
	{
		player_rotate(mlx, map, img, c);
		img->img_pl->instances[0].y += map->tile_sq;
		map->pl_y++;
	}
	completion_checker(mlx, map, img);
}

void	move_hook(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = param;
	if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(map->mlx);
	if (mlx_is_key_down(map->mlx, MLX_KEY_UP) && keydata.action == MLX_PRESS)
		player_moving(map->mlx, map, map->img, 'w');
	if (mlx_is_key_down(map->mlx, MLX_KEY_DOWN) && keydata.action == MLX_PRESS)
		player_moving(map->mlx, map, map->img, 's');
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT) && keydata.action == MLX_PRESS)
		player_moving(map->mlx, map, map->img, 'a');
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT) && keydata.action == MLX_PRESS)
		player_moving(map->mlx, map, map->img, 'd');
}
