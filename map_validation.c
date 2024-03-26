/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:04:02 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/03/26 17:04:03 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_validation(t_map *map)
{
	int32_t	fd;
	char	*line;

	fd = open(map->filename, O_RDONLY);
	if (fd == -1)
	{
		puts("Error\nMap file not found");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line > 0)
	{
		map->line_count++;
		if (map->line_length == 0)
			map->line_length = strlen(line);
		if ((unsigned long)map->line_length != strlen(line))
		{
			puts("Error\nMap is not rectangular");
			exit(EXIT_FAILURE);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}
