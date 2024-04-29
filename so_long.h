/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:18:59 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/04/29 16:56:21 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <MLX42/MLX42.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft/libft.h"

# define WIDTH 1366
# define HEIGHT 736
# define TILE_SIZE 64

typedef struct s_img
{
	mlx_texture_t	*txt_pl;
	mlx_texture_t	*txt_free;
	mlx_texture_t	*txt_exit;
	mlx_texture_t	*txt_wall;
	mlx_texture_t	*txt_col;
	mlx_texture_t	*txt_pl_left;
	mlx_texture_t	*txt_pl_collect;
	mlx_image_t		*img_pl;
	mlx_image_t		*img_pl_left;
	mlx_image_t		*img_pl_collect;
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
	int			pl_pos;
	mlx_t		*mlx;
	t_img		*img;
}	t_map;

void	move_hook(mlx_key_data_t keydata, void *param);
void	initialize_map_values(t_map *map);
void	completion_checker(mlx_t *mlx, t_map *map, t_img *img);
void	player_rotate(mlx_t *mlx, t_map *map, t_img *img, char c);
void	player_moving(mlx_t *mlx, t_map *map, t_img *img, char c);
void	move_hook(mlx_key_data_t keydata, void *param);
void	render_player(mlx_t *mlx, t_img *img, t_map *map);
int		render_map(mlx_t *mlx, t_map *map, t_img *img);
void	check_map(t_map *map);
int		count_lines(int fd, t_map *map, int bytes_read);
void	mapping(t_map *map);
void	map_validation(t_map *map);
int32_t	main(int argc, char **argv);

int		route_validation(t_map *map);
void	parse_way(char **grid_cpy, size_t i, size_t j, t_map *map);
void	line_validation(t_map *map, char **grid_cpy);
void	malloc_error(t_map *map, char **grid, int check);
void	free_grid(t_map *map, char **grid);

void	preload_images(mlx_t *mlx, t_img *img, t_map *map);

int		open_map_file(t_map *map);
void	populate_grid(t_map *map);
void	check_game_elements(t_map *map);
void	check_map_surrounded_by_walls(t_map *map);
void	exit_with_error(t_map *map, char *message);
void	map_sizing(t_map *map);

#endif