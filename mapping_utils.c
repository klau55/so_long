/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:48:56 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/04/30 13:55:44 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	open_map_file(t_map *map)
{
	int	fd;

	fd = open(map->filename, O_RDONLY);
	if (fd == -1)
		return (0);
	return (fd);
}

void	populate_grid(t_map *map)
{
	int	i;

	i = 0;
	map->grid = (char **)malloc(sizeof(char *) * map->line_count);
	if (!map->grid)
		exit_with_error(map, "Error\n");
	while (i < map->line_count)
	{
		map->grid[i] = get_next_line(map->fd);
		i++;
	}
	map->line_length = ft_strlen(map->grid[0]);
	i = 0;
	while (i < map->line_count)
	{
		if ((int)ft_strlen(map->grid[i]) != map->line_length)
		{
			if (i + 1 == map->line_count)
				break ;
			exit_with_error(map, "Error, map not rectangular\n");
		}
		i++;
	}
}

void	check_game_elements(t_map *map)
{
	if (map->col_c == 0 || map->pl_c != 1 || map->ex_c != 1)
		exit_with_error(map, "Error, check map elements\n");
	if (map->col_c < 1 || map->line_count < 3 || map->line_length < 3)
		exit_with_error(map, "Error, no collectible or map too shmoll\n");
}

void	check_map_surrounded_by_walls(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->line_length - 1)
	{
		if (map->grid[0][i] != '1' || map->grid[map->line_count - 1][i] != '1')
			exit_with_error(map, "Error, check wall mapping\n");
		i++;
	}
	i = 0;
	while (i < map->line_count - 1)
	{
		if (map->grid[i][0] != '1' || map->grid[i][map->line_length - 2] != '1')
			exit_with_error(map, "Error, check wall mapping\n");
		i++;
	}
}

void	exit_with_error(t_map *map, char *message)
{
	ft_putstr_fd(message, 2);
	if (map->grid)
		free_grid(map, map->grid);
	if (map->mlx)
	{
		mlx_terminate(map->mlx);
		mlx_close_window(map->mlx);
	}
	exit(EXIT_FAILURE);
}
