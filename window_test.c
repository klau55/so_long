/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:44:33 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/03/01 16:18:32 by nkarpilo         ###   ########.fr       */
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
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define WIDTH 1024
#define HEIGHT 768

void	move_hook(mlx_key_data_t keydata, void *param);
char	*get_next_line(int fd);

// -----------------------------------------------------------------------------

typedef struct s_img
{
	mlx_texture_t	*txt_pl;
	mlx_texture_t	*txt_free;
	mlx_texture_t	*txt_exit;
	mlx_texture_t	*txt_wall;
	mlx_texture_t	*txt_col;
	mlx_image_t		*img_pl;
	mlx_image_t		*img_free;
	mlx_image_t		*img_exit;
	mlx_image_t		*img_wall;
	mlx_image_t		*img_col;
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

void	initialize_map_values(t_map *map)
{
	map->ex_c = 0;
	map->col_c = 0;
	map->pl_c = 0;
	map->line_count = 0;
	map->wnd_w = 1366;
	map->wnd_h = 768;
	map->moves = 0;
	map->col_col = 0;
	map->n = 0;
	map->check = 1;
}

void	player_moving(t_map *map, t_img *img, char c)
{
	if ((c == 'a') && (map->grid[map->pl_y][map->pl_x - 1] != '1'))
	{
		img->img_pl->instances[0].x -= map->tile_sq;
		map->pl_x--;
	}
	if ((c == 'd') && (map->grid[map->pl_y][map->pl_x + 1] != '1'))
	{
		img->img_pl->instances[0].x += map->tile_sq;
		map->pl_x++;
	}
	if ((c == 'w') && (map->grid[map->pl_y - 1][map->pl_x] != '1'))
	{
		img->img_pl->instances[0].y -= map->tile_sq;
		map->pl_y--;
	}
	if ((c == 's') && (map->grid[map->pl_y + 1][map->pl_x] != '1'))
	{
		img->img_pl->instances[0].y += map->tile_sq;
		map->pl_y++;
	}
	map->moves++;
	printf("Number of movements: %d\n", map->moves);
}

void	move_hook(mlx_key_data_t keydata, void *param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP) && (keydata.action == MLX_PRESS))
		player_moving(map, img, 'w');
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN) && (keydata.action == MLX_PRESS))
		player_moving(map, img, 's');
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT) && (keydata.action == MLX_PRESS))
		player_moving(map, img, 'a');
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT) && (keydata.action == MLX_PRESS))
		player_moving(map, img, 'd');
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
	if (mlx_image_to_window(mlx, img->img_pl, map->pl_x * map->tile_sq, \
	map->pl_y * map->tile_sq) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	return (0);
}

int	render_map(mlx_t *mlx)
{

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
	map->tile_sq = 64;
	// bad solution
	map->line_length--;
	while (map->y < map->line_count)
	{
		while (map->x < map->line_length)
		{
			mlx_image_to_window(mlx, img->img_free, \
			map->x * map->tile_sq, map->y * map->tile_sq);
			if (map->grid[map->y][map->x] == 'E')
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
			if (map->grid[map->y][map->x] == '1')
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
			if (map->grid[map->y][map->x] == 'C')
			{
				img->txt_col = mlx_load_png("./assets/collectible.png");
				img->img_col = mlx_texture_to_image(mlx, img->txt_col);
				if (!img->img_col)
				{
					mlx_close_window(mlx);
					puts(mlx_strerror(mlx_errno));
					return (EXIT_FAILURE);
				}
				mlx_resize_image(img->img_col, 32, 32);
				mlx_image_to_window(mlx, img->img_col, \
				map->x * map->tile_sq, map->y * map->tile_sq);
			}
			if (map->grid[map->y][map->x] == 'P')
			{
				map->pl_x = map->x;
				map->pl_y = map->y;
			}
			map->x++;
		}
		map->y++;
		map->x = 0;
	}
	/////////////////
	return (0);
}

void	check_map(t_map *map)
{
	map->fd = open("map.ber", O_RDONLY);
	if (map->fd == -1)
	{
		puts("Error\n");
		exit(1);
	}
	map->bytes_read = read(map->fd, NULL, 0);

}

int	count_lines(int fd, t_map *map)
{
	char	buffer[1];
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read != 0)
	{
		bytes_read = read(fd, buffer, 1);
		if (bytes_read < 0)
			return (0);
		if (buffer[0] == 'C')
			map->col_c++;
		if (buffer[0] == 'P')
			map->pl_c++;
		if (buffer[0] == 'E')
			map->ex_c++;
		if (bytes_read > 0 && buffer[0] == '\n')
			map->line_count++;
		if (buffer[0] != '\n' && buffer[0] != '0' && buffer[0] != '1' \
			&& buffer[0] != 'C' && buffer[0] != 'P' && buffer[0] != 'E')
		{
			printf("Error\nInvalid characters: %c\n", buffer[0]);
			exit(EXIT_FAILURE);
		}
	}
	map->line_count++;
	return (1);
}

void	mapping(t_map *map)
{
	int	i;

	map->fd = open("map.ber", O_RDONLY);
	if (map->fd == -1)
	{
		puts("Error\n");
		map->fd = close(map->fd);
		exit(1);
	}
	if (!count_lines(map->fd, map))
	{
		puts("Error\n");
		map->fd = close(map->fd);
		exit(1);
	}
	printf("line_count: %d\n", map->line_count);
	/////
	close(map->fd);
	map->fd = open("map.ber", O_RDONLY);
	map->grid = (char **)malloc(sizeof(char *) * map->line_count);
	if (!map->grid)
	{
		puts("Error\n");
		exit(1);
	}
	i = 0;
	while (i < map->line_count)
	{
		map->grid[i] = get_next_line(map->fd);
		printf("map->grid[i]: %s\n", map->grid[i]);
		i++;
	}
	map->line_length = strlen(map->grid[0]);
	close(map->fd);
	// check all lines are the same length
	return ;
}


int32_t	main(void)
{
	mlx_t			*mlx;

	img = (t_img *)malloc(sizeof(t_img));
	map = (t_map *)malloc(sizeof(t_map));
	map->filename = "map.ber";
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "solo ng", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	initialize_map_values(map);
	mapping(map);
	render_map(mlx);
	printf("sasadasd\n");
	render_player(mlx, img);
	mlx_key_hook(mlx, move_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
