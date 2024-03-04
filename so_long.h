#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <MLX42/MLX42.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>

# define WIDTH 1024
# define HEIGHT 768

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

void	move_hook(mlx_key_data_t keydata, void *param);
char	*get_next_line(int fd);
void	initialize_map_values(t_map *map);
void	completion_checker(mlx_t *mlx, t_map *map, t_img *img);
void	player_rotate(mlx_t *mlx, t_map *map, t_img *img, char c);
void	player_moving(mlx_t *mlx, t_map *map, t_img *img, char c);
void	move_hook(mlx_key_data_t keydata, void *param);
int	render_player(mlx_t *mlx, t_img *img, t_map *map);
int	render_map(mlx_t *mlx, t_map *map, t_img *img);
void	check_map(t_map *map);
int	count_lines(int fd, t_map *map);
void	mapping(t_map *map);
int32_t	main(void);

#endif