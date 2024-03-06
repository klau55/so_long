#include "so_long.h"

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

int	render_player(mlx_t *mlx, t_img *img, t_map *map)
{
	img->txt_pl = mlx_load_png("assets/monky_right.png");
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
	if (mlx_image_to_window(mlx, img->img_pl, (map->pl_x * map->tile_sq) + 15, \
	map->pl_y * map->tile_sq) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	return (0);
}

int	render_map(mlx_t *mlx, t_map *map, t_img *img)
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
				img->txt_col = mlx_load_png("./assets/book.png");
				img->img_col = mlx_texture_to_image(mlx, img->txt_col);
				if (!img->img_col)
				{
					mlx_close_window(mlx);
					puts(mlx_strerror(mlx_errno));
					return (EXIT_FAILURE);
				}
				mlx_resize_image(img->img_col, 25, 30);
				mlx_image_to_window(mlx, img->img_col, \
				map->x * map->tile_sq + 20, map->y * map->tile_sq + 20);
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
	map->fd = open(map->filename, O_RDONLY);
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

	map->fd = open(map->filename, O_RDONLY);
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
	//printf("line_count: %d\n", map->line_count);
	/////
	close(map->fd);
	map->fd = open(map->filename, O_RDONLY);
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
	// check amount of players, collectibles and exits
	// check if map is rectangular
	// check if map is surrounded by walls
	return ;
}
