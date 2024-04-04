/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:04:05 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/04/04 18:54:17 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	resize_handle_images(mlx_t *mlx, t_img *img, t_map *map)
{
	mlx_delete_image(mlx, img->img_free);
	mlx_delete_image(mlx, img->img_pl);
	mlx_delete_image(mlx, img->img_exit);
	mlx_delete_image(mlx, img->img_wall);
	mlx_delete_image(mlx, img->img_col);
	img->img_free = mlx_texture_to_image(mlx, img->txt_free);
	img->img_pl = mlx_texture_to_image(mlx, img->txt_pl);
	img->img_exit = mlx_texture_to_image(mlx, img->txt_exit);
	img->img_wall = mlx_texture_to_image(mlx, img->txt_wall);
	img->img_col = mlx_texture_to_image(mlx, img->txt_col);
	mlx_resize_image(img->img_free, map->tile_sq, map->tile_sq);
	mlx_resize_image(img->img_pl, map->tile_sq / 2, 64);
	mlx_resize_image(img->img_exit, map->tile_sq, map->tile_sq);
	mlx_resize_image(img->img_wall, map->tile_sq, map->tile_sq);
	mlx_resize_image(img->img_col, map->tile_sq / 2.5, map->tile_sq / 2);
}

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_map	*map;

	map = (t_map *)param;
	map->wnd_w = width;
	map->wnd_h = height;
	resize_handle_images(map->mlx, map->img, map);
	render_map(map->mlx, map, map->img);
}
