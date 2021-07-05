/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 12:59:26 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/05 16:03:36 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

//TODO: que me puedan pasar colores
int	parse_map(t_map_data *map, char *map_file)
{
	int		fd;
	int 	ret;
	char	*line;
	char	**numbers_in_line;
	int		x;
	int		y;
	int		i;

	map->map_width = 0;
	map->map_height = 0;
	map->map_array = NULL;

	fd = open(map_file, O_RDONLY);
	ret = get_next_line(fd, &line);
	if (ret <= 0)
		return (error_custom("Error: empty map or gnl error", 0));
	numbers_in_line = ft_split(line, ' ');
	if (!numbers_in_line)
		return (error_message(0));
	while (numbers_in_line[map->map_width])
		map->map_width++;
	free_string_array(numbers_in_line);
	while (ret > 0)
	{
		map->map_height++;
		free(line);
		ret = get_next_line(fd, &line);
	}
	if (ret == -1)
		return (error_custom("Error: there was an error in get_next_line", 0));
	free(line);
	close(fd);

	printf("map_height: %d, map_width: %d\n", map->map_height, map->map_width);
	map->map_array = malloc(map->map_height * sizeof(int*));
	if (!map->map_array)
		return (error_message(0));
	i = 0;
	while (i < map->map_height)
	{
		map->map_array[i] = malloc(map->map_width * sizeof(int));
		if (!map->map_array[i])
			return (error_message(0));
		i++;
	}

	fd = open(map_file, O_RDONLY);
	ret = get_next_line(fd, &line);
	y = 0;
	while (ret > 0)
	{
		numbers_in_line = ft_split(line, ' ');
		if (!numbers_in_line)
			return (error_message(0));
		x = 0;
		while (numbers_in_line[x])
		{
			map->map_array[y][x] = ft_atoi(numbers_in_line[x]);
			x++;
		}
		y++;
		free_string_array(numbers_in_line);
		free(line);
		ret = get_next_line(fd, &line);
	}
	if (ret == -1)
		return (error_custom("Error: there was an error in get_next_line", 0));
	free(line);
	return (1);
}