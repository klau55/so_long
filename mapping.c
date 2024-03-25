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

void	map_sizing(t_map *map)
{
	map->tile_l = map->wnd_w / (map->line_length - 1);
	map->tile_w = map->wnd_h / map->line_count;
	if (map->tile_l <= map->tile_w)
		map->tile_sq = map->tile_l;
	else
		map->tile_sq = map->tile_w;
	printf(">>>>map->tile_sq: %d\n", map->tile_sq);
}

int	render_player(mlx_t *mlx, t_img *img, t_map *map)
{
	mlx_resize_image(img->img_pl, map->tile_sq, map->tile_sq);
	mlx_image_to_window(mlx, img->img_pl, \
		(map->pl_x * map->tile_sq), map->pl_y * map->tile_sq);
	return (0);
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
	printf("SRAKA 2");
	map_sizing(map);
	img->txt_free = mlx_load_png("./assets/floor_tile.png");
	img->txt_exit = mlx_load_png("./assets/exit.png");
	img->txt_wall = mlx_load_png("./assets/wall.png");
	img->txt_col = mlx_load_png("./assets/book.png");
	img->txt_pl = mlx_load_png("assets/monky_right.png");
	img->img_free = mlx_texture_to_image(mlx, img->txt_free);
	img->img_exit = mlx_texture_to_image(mlx, img->txt_exit);
	img->img_wall = mlx_texture_to_image(mlx, img->txt_wall);
	img->img_col = mlx_texture_to_image(mlx, img->txt_col);
	img->img_pl = mlx_texture_to_image(mlx, img->txt_pl);
	mlx_resize_image(img->img_free, map->tile_sq, map->tile_sq);
	mlx_resize_image(img->img_exit, map->tile_sq, map->tile_sq);
	mlx_resize_image(img->img_wall, map->tile_sq, map->tile_sq);
	mlx_resize_image(img->img_col, (map->tile_sq / 2.5), map->tile_sq / 2);
	mlx_resize_image(img->img_pl, map->tile_sq / 2, map->tile_sq);
}

int	render_map(mlx_t *mlx, t_map *map, t_img *img)
{
	// TODO: line length must be -1 
	// TODO: 
	map->x = 0;
	map->y = 0;
	map_sizing(map);
	if (!img->img_pl)
		preload_images(mlx, img, map);
	while (map->y < map->line_count)
	{
		if (!img->img_free || !img->img_exit || !img->img_wall || !img->img_col)
		{
			printf("5555\n");
			mlx_close_window(mlx);
			puts(mlx_strerror(mlx_errno));
			return (EXIT_FAILURE);
		}
		while (map->x < map->line_length - 1)
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
	i = 0;
	// check all lines are the same length
	while (i < map->line_count)
	{
		printf("strlen(map->grid[i]): %lu\n", strlen(map->grid[i]));
		printf("map->line_length: %d\n", map->line_length);
		if ((int)strlen(map->grid[i]) != map->line_length)
		{
			if (i + 1 == map->line_count)
				break ;
			puts("Error\n");
			exit(1);
		}
		i++;
	}
	// check amount of players, collectibles and exits
	if (map->col_c == 0 || map->pl_c != 1 || map->ex_c != 1)
	{
		puts("Erroramt1\n");
		exit(1);
	}
	if (map->col_c < 1 || map->line_count < 3 || map->line_length < 3)
	{
		puts("Erroramt2\n");
		exit(1);
	}
	// check path
	if (!route_validation(map))
	{
		puts("Error! No possible route\n");
		exit(1);
	}
	// check if map is surrounded by walls
	i = 0;
	while (i < map->line_length - 1)
	{
		if (map->grid[0][i] != '1' || map->grid[map->line_count - 1][i] != '1')
		{
			puts("Errorprelast\n");
			exit(1);
		}
		i++;
	}
	i = 0;
	while (i < map->line_count - 1)
	{
		if (map->grid[i][0] != '1' || map->grid[i][map->line_length - 2] != '1')
		{
			puts("Errorlast\n");
			exit(1);
		}
		i++;
	}


	close(map->fd);

	return ;
}
