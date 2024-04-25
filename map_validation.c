/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:04:02 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/04/25 19:58:20 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_validation(t_map *map)
{
	int32_t	fd;
	char	*line;

	fd = open(map->filename, O_RDONLY);
	if (fd == -1)
		exit_with_error(map, "Error\nMap file not found");
	line = get_next_line(fd);
	while (line > 0)
	{
		map->line_count++;
		if (map->line_length == 0)
			map->line_length = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}
