/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:44:33 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/02/28 17:48:36 by nkarpilo         ###   ########.fr       */
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



// -----------------------------------------------------------------------------

typedef struct s_img
{
	mlx_texture_t	*txt_pl;
	mlx_image_t		*img_pl;
}	t_img;

static t_img* img;

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		img->img_pl->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		img->img_pl->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		img->img_pl->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		img->img_pl->instances[0].x += 5;
}
/*
int	render_player(mlx_t *mlx, mlx_image_t *image, mlx_texture_t *texture)
{
	texture = mlx_load_png("assets/monky.png");
	if (!texture)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	image = mlx_texture_to_image(mlx, texture);
	if (!image)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	mlx_resize_image(image, 64, 128);
	return (0);
} */


int32_t	main(void)
{
	mlx_t			*mlx;

	img = (t_img *)malloc(sizeof(t_img));
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "solo ng", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
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
	mlx_resize_image(img->img_pl, 64, 128);
	if (mlx_image_to_window(mlx, img->img_pl, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
