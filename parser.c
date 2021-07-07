/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 12:59:26 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/07 12:22:16 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "gnl/get_next_line.h"
#include <fcntl.h>

static int	count_map_size(t_map_data *map, const char *map_file)
{
	int		fd;
	int		ret;
	char	*line;
	char	**numbers_in_one_line;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (error_message(0));
	ret = get_next_line(fd, &line);
	if (ret <= 0)
		return (error_custom("Error: empty map or gnl error", 0));
	numbers_in_one_line = ft_split(line, ' ');
	if (!numbers_in_one_line)
		return (error_message(0));
	while (numbers_in_one_line[map->map_width])
		map->map_width++;
	free_string_array(numbers_in_one_line);
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
	return (1);
}

static int	allocate_map(t_map_data *map)
{
	int	i;

	map->map_array = malloc(map->map_height * sizeof(int *));
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
	return (1);
}

static void	fill_map_array(int **map_array, char **numbers_in_line, int y)
{
	int	x;

	x = 0;
	while (numbers_in_line[x])
	{
		map_array[y][x] = ft_atoi(numbers_in_line[x]);
		x++;
	}
}

static int	save_numbers_into_map(t_map_data *map, const char *map_file)
{
	int		fd;
	int		ret;
	char	*line;
	char	**numbers_in_line;
	int		y;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (error_message(0));
	ret = get_next_line(fd, &line);
	y = 0;
	while (ret > 0)
	{
		numbers_in_line = ft_split(line, ' ');
		if (!numbers_in_line)
			return (error_message(0));
		fill_map_array(map->map_array, numbers_in_line, y);
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

//TODO: que me puedan pasar colores
int	parse_map(t_map_data *map, const char *map_file)
{
	map->map_width = 0;
	map->map_height = 0;
	map->map_array = NULL;
	if (!count_map_size(map, map_file))
		return (0);
	if (!allocate_map(map))
		return (0);
	if (!save_numbers_into_map(map, map_file))
		return (0);
	return (1);
}
