/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 12:59:26 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/16 16:11:03 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#include "../libft/get_next_line.h"
#include <fcntl.h>

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
	map->color_array = malloc(map->map_height * map->map_width * sizeof(int));
	if (!map->color_array)
		return (error_message(0));
	return (1);
}

static void	fill_map_array(t_map_data *map, char **numbers_in_line, int y)
{
	int		x;
	int		index;
	char	*color;

	x = 0;
	while (numbers_in_line[x])
	{
		map->map_array[y][x] = ft_atoi(numbers_in_line[x]);
		index = get_index(x, y, map->map_width);
		color = ft_strchr(numbers_in_line[x], ',');
		if (color)
			map->color_array[index] = ft_atoi_base(color + 1, 16);
		else
			map->color_array[index] = 0xFFFFFF;
		x++;
	}
}

static int	save_numbers_into_map(t_map_data *map, int fd)
{
	int		ret;
	char	*line;
	char	**numbers_in_line;
	int		y;

	ret = get_next_line(fd, &line);
	y = 0;
	while (ret > 0)
	{
		numbers_in_line = ft_split(line, ' ');
		if (!numbers_in_line)
			return (error_message(0));
		fill_map_array(map, numbers_in_line, y);
		y++;
		free_string_array(numbers_in_line);
		free(line);
		ret = get_next_line(fd, &line);
	}
	if (ret == -1)
		return (error_custom("there was an error in get_next_line", 0));
	free(line);
	return (1);
}

int	parse_map(t_map_data *map, const char *map_file)
{
	int	fd;

	map->map_width = 0;
	map->map_height = 0;
	map->map_array = NULL;
	map->color_array = NULL;
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (error_message(0));
	if (!count_map_size(map, fd))
		return (0);
	if (!allocate_map(map))
		return (0);
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (error_message(0));
	if (!save_numbers_into_map(map, fd))
		return (0);
	return (1);
}
