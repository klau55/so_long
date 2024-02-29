/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:44:33 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/02/29 19:05:01 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>

#define WIDTH 1024
#define HEIGHT 768

void	move_hook(mlx_key_data_t keydata, void *param);

// -----------------------------------------------------------------------------

typedef struct s_img
{
	mlx_texture_t	*txt_pl;
	mlx_texture_t	*txt_free;
	mlx_texture_t	*txt_exit;
	mlx_texture_t	*txt_wall;
	mlx_image_t		*img_pl;
	mlx_image_t		*img_free;
	mlx_image_t		*img_exit;
	mlx_image_t		*img_wall;
}	t_img;

typedef struct s_map
{
	int			name_length;
	int			fd;
	int			bytes_read;
	const char	*filename;
	char		**grid;
	int			line_count;
	int			line_length;
	int			col_c;
	int			pl_c;
	int			ex_c;
	int			col_col;
	int			tile_w;
	int			tile_l;
	int			tile_sq;
	int			pl_x;
	int			pl_y;
	int			ex_x;
	int			ex_y;
	int			moves;
	int			check;
	int			x;
	int			y;
	int			n;
	int			wnd_w;
	int			wnd_h;
	mlx_t		*mlx;
	t_img		*img;
}	t_map;


static t_map* map;
static t_img* img;

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	move_hook(mlx_key_data_t keydata, void *param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP) && (keydata.action == MLX_PRESS))
		img->img_pl->instances[0].y -= map->tile_sq;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN) && (keydata.action == MLX_PRESS))
		img->img_pl->instances[0].y += map->tile_sq;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT) && (keydata.action == MLX_PRESS))
		img->img_pl->instances[0].x -= map->tile_sq;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT) && (keydata.action == MLX_PRESS))
		img->img_pl->instances[0].x += map->tile_sq;
}

int	render_player(mlx_t *mlx, t_img *img)
{
	img->txt_pl = mlx_load_png("assets/monky.png");
	if (!img->txt_pl)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	img->img_pl = mlx_texture_to_image(mlx, img->txt_pl);
	if (!img->img_pl)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	mlx_resize_image(img->img_pl, 32, 64);
	if (mlx_image_to_window(mlx, img->img_pl, 75, 64) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	return (0);
}

int	render_map(mlx_t *mlx)
{
	map->ex_c = 0;
	map->col_c = 0;
	map->pl_c = 0;
	map->line_count = 10;
	map->line_length = 10;
	map->wnd_w = 1366;
	map->wnd_h = 768;
	map->moves = 0;
	map->col_col = 0;
	map->n = 0;
	map->check = 1;
	img->txt_free = mlx_load_png("./assets/floor_tile.png");
	img->img_free = mlx_texture_to_image(mlx, img->txt_free);
	if (!img->img_free)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	mlx_resize_image(img->img_free, 64, 64);
	map->x = 0;
	map->y = 0;
	// sadasdasdasdasd
	map->tile_l = map->wnd_w / (map->line_length - 1);
	map->tile_w = map->wnd_h / map->line_count;
	if (map->tile_l <= map->tile_w)
		map->tile_sq = map->tile_l;
	else
		map->tile_sq = map->tile_w;
	printf("tile_sq: %d\n", map->tile_sq);
	printf("tile_l: %d\n", map->tile_l);
	printf("tile_w: %d\n", map->tile_w);
	map->tile_sq = 64;
	while (map->y < map->line_count)
	{
		while (map->x < map->line_length)
		{
			mlx_image_to_window(mlx, img->img_free, \
			map->x * map->tile_sq, map->y * map->tile_sq);
			if (map->x == map->line_length - 3 && map->y == map->line_count - 2)
			{
				img->txt_exit = mlx_load_png("./assets/exit.png");
				img->img_exit = mlx_texture_to_image(mlx, img->txt_exit);
				if (!img->img_exit)
				{
					mlx_close_window(mlx);
					puts(mlx_strerror(mlx_errno));
					return (EXIT_FAILURE);
				}
				mlx_resize_image(img->img_exit, 64, 64);
				mlx_image_to_window(mlx, img->img_exit, \
				map->x * map->tile_sq, map->y * map->tile_sq);
			}
			if (map->x == map->line_length - 1 || map->x == 0 || \
			map->y == 0 || map->y == map->line_count -1)
			{
				img->txt_wall = mlx_load_png("./assets/wall.png");
				img->img_wall = mlx_texture_to_image(mlx, img->txt_wall);
				if (!img->img_wall)
				{
					mlx_close_window(mlx);
					puts(mlx_strerror(mlx_errno));
					return (EXIT_FAILURE);
				}
				mlx_resize_image(img->img_wall, 64, 64);
				mlx_image_to_window(mlx, img->img_wall, \
				map->x * map->tile_sq, map->y * map->tile_sq);
			}
			map->x++;
		}
		map->y++;
		map->x = 0;
	}
	/////////////////
	return (0);
}


int32_t	main(void)
{
	mlx_t			*mlx;

	img = (t_img *)malloc(sizeof(t_img));
	map = (t_map *)malloc(sizeof(t_map));
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "solo ng", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	render_map(mlx);
	render_player(mlx, img);
	mlx_key_hook(mlx, move_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
