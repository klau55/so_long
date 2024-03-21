#include "so_long.h"

void	free_grid(t_map *map, char **grid)
{
	int	i;

	i = 0;
	while (i < map->line_count)
	{
		free(grid[i]);
		grid[i] = NULL;
		i++;
	}
	free(grid);
	grid = NULL;
}

void	malloc_error(t_map *map, char **grid, int check)
{
	if (check == 1)
		free_grid(map, grid);
	puts("Error\nMalloc error\n");
	exit(1);
}
