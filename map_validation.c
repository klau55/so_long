/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:04:02 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/05/02 18:31:01 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_validation(t_map *map)
{
	int32_t	fd;
	char	*line;
	int		line_len;

	fd = open(map->filename, O_RDONLY);
	if (fd == -1)
		exit_with_error(map, "Error\nMap file not found");
	else if (read(fd, NULL, 0) == -1)
		exit_with_error(map, "Error\nMap file not readable");
	line = get_next_line(fd);
	while (line > 0)
	{
		map->line_count++;
		line_len = ft_strlen(line);
		if (line[line_len] == '\0')
			line_len--;
		if (!map->line_length || map->line_length == 0)
			map->line_length = line_len;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}
