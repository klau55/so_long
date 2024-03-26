/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:03:57 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/03/26 17:04:51 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	count_lines(int fd, t_map *map, int bytes_read)
{
	char	buffer[1];

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
	map->fd = open_map_file(map);
	if (!map->fd)
		exit_with_error(map, "Error\n");

	if (!count_lines(map->fd, map, 1))
		exit_with_error(map, "Error\n");

	close(map->fd);

	map->fd = open_map_file(map);
	allocate_memory_for_grid(map);

	populate_grid(map);

	check_line_lengths(map);

	check_game_elements(map);

	if (!route_validation(map))
		exit_with_error(map, "Error! No possible route\n");

	check_map_surrounded_by_walls(map);

	close(map->fd);
}

int	open_map_file(t_map *map)
{
	int	fd;

	fd = open(map->filename, O_RDONLY);
	if (fd == -1)
		return (0);
	return (fd);
}

void	allocate_memory_for_grid(t_map *map)
{
	map->grid = (char **)malloc(sizeof(char *) * map->line_count);
	if (!map->grid)
		exit_with_error(map, "Error\n");
}

void	populate_grid(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->line_count)
	{
		map->grid[i] = get_next_line(map->fd);
		printf("map->grid[i]: %s\n", map->grid[i]);
		i++;
	}
	map->line_length = strlen(map->grid[0]);
}

void	check_line_lengths(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->line_count)
	{
		printf("strlen(map->grid[i]): %lu\n", strlen(map->grid[i]));
		printf("map->line_length: %d\n", map->line_length);
		if ((int)strlen(map->grid[i]) != map->line_length)
		{
			if (i + 1 == map->line_count)
				break ;
			exit_with_error(map, "Error\n");
		}
		i++;
	}
}

void	check_game_elements(t_map *map)
{
	if (map->col_c == 0 || map->pl_c != 1 || map->ex_c != 1)
		exit_with_error(map, "Erroramt1\n");
	if (map->col_c < 1 || map->line_count < 3 || map->line_length < 3)
		exit_with_error(map, "Erroramt2\n");
}

void	check_map_surrounded_by_walls(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->line_length - 1)
	{
		if (map->grid[0][i] != '1' || map->grid[map->line_count - 1][i] != '1')
			exit_with_error(map, "Errorprelast\n");
		i++;
	}
	i = 0;
	while (i < map->line_count - 1)
	{
		if (map->grid[i][0] != '1' || map->grid[i][map->line_length - 2] != '1')
			exit_with_error(map, "Errorlast\n");
		i++;
	}
}

void	exit_with_error(t_map *map, char *message)
{
	puts(message);
	if (map->grid)
		free_grid(map, map->grid);
	exit(1);
}
