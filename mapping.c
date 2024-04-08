/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:03:57 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/04/08 19:10:18 by nkarpilo         ###   ########.fr       */
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
	map->pl_pos = 0;
}

void	map_sizing(t_map *map)
{
	map->tile_l = map->wnd_w / (map->line_length - 1);
	map->tile_w = map->wnd_h / map->line_count;
	if (map->tile_l <= map->tile_w)
		map->tile_sq = map->tile_l;
	else
		map->tile_sq = map->tile_w;
}

void	check_map(t_map *map)
{
	map->fd = open(map->filename, O_RDONLY);
	if (map->fd == -1)
	{
		ft_printf("Error\n");
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
			ft_printf("Error\nInvalid characters");
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
	populate_grid(map);
	check_game_elements(map);
	if (!route_validation(map))
		exit_with_error(map, "Error! No possible route\n");
	check_map_surrounded_by_walls(map);
	close(map->fd);
}
