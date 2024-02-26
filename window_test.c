/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:44:33 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/02/26 16:49:40 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/MLX42/MLX42.h"

#define WIDTH 1024
#define HEIGHT 1024

static mlx_image_t* image;

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	(void)param;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

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

typedef struct s_img
{
	mlx_texture_t	*txt_free;
	mlx_texture_t	*txt_obs;
	mlx_texture_t	*txt_c;
	mlx_texture_t	*txt_e;
	mlx_texture_t	*txt_e_o;
	mlx_texture_t	*txt_pl;
	mlx_image_t		*img_free;
	mlx_image_t		*img_obs;
	mlx_image_t		*img_c;
	mlx_image_t		*img_e;
	mlx_image_t		*img_e_o;
	mlx_image_t		*img_pl;
}	t_img;
int32_t main(void)
{
	mlx_t* mlx;
	t_img *img = NULL;
	t_map *map = NULL;

	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "KYPBA 123", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	img->txt_pl = mlx_load_png("assets/monk.png");
	printf("ass\n");
	img->img_pl = mlx_texture_to_image(mlx, img->txt_pl);
	mlx_resize_image(img->img_pl, 64, 64);
	image = img->img_pl;
	if (!(image = mlx_new_image(mlx, 64, 64)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}