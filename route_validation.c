#include "so_long.h"

void	parse_way(char **grid_cpy, size_t i, size_t j)
{
	if (grid_cpy[i + 1][j] == '0' || grid_cpy[i + 1][j] == 'C'\
	|| grid_cpy[i + 1][j] == 'E')
	{
		grid_cpy[i + 1][j] = 'x';
	}
	if (grid_cpy[i - 1][j] == '0' || grid_cpy[i - 1][j] == 'C'\
	|| grid_cpy[i - 1][j] == 'E')
	{
		grid_cpy[i - 1][j] = 'x';
	}
	if (grid_cpy[i][j + 1] == '0' || grid_cpy[i][j + 1] == 'C'\
	|| grid_cpy[i][j + 1] == 'E')
	{
		grid_cpy[i][j + 1] = 'x';
	}
	if (grid_cpy[i][j - 1] == '0' || grid_cpy[i][j - 1] == 'C'\
	|| grid_cpy[i][j - 1] == 'E')
	{
		grid_cpy[i][j - 1] = 'x';
	}
	grid_cpy[i][j] = '*';
}

void	line_validation(t_map *map, char **grid_cpy)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->check != 0)
	{
		map->check = 0;
		while (i < map->line_count)
		{
			j = 0;
			while (j < map->line_length)
			{
				if (grid_cpy[i][j] == 'P' || grid_cpy[i][j] == 'x')
				{
					parse_way(grid_cpy, i, j);
					map->check = 1;
				}
				j++;
			}
			i++;
		}
		i = 0;
	}
}


int	route_validation(t_map *map)
{
	char	**grid_cpy;
	int		i;

	grid_cpy = (char **)malloc(sizeof(char *) * map->line_count);
	if (!grid_cpy)
		malloc_error(map, map->grid, 1);
	i = 0;
	while (i < map->line_count)
	{
		grid_cpy[i] = strdup(map->grid[i]);
		i++;
	}
	line_validation(map, grid_cpy);
	i = 0;
	while (i < map->line_count)
	{
		if (strchr(grid_cpy[i], 'E') || strchr(grid_cpy[i], 'C'))
		{
			free_grid(map, grid_cpy);
			return (0);
		}
		i++;
	}
	free_grid(map, grid_cpy);
	return (1);
}
