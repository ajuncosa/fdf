/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 17:45:40 by anajuncosa        #+#    #+#             */
/*   Updated: 2021/07/16 16:11:07 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#include "../libft/get_next_line.h"

static int	count_line_width(t_map_data *map, char *line)
{
	int		count;
	char	**numbers_in_one_line;

	count = 0;
	numbers_in_one_line = ft_split(line, ' ');
	if (!numbers_in_one_line)
		return (error_message(0));
	while (numbers_in_one_line[count])
		count++;
	if (map->map_width != 0 && count != map->map_width)
		return (error_custom("all lines in map must have the same width", 0));
	map->map_width = count;
	free_string_array(numbers_in_one_line);
	return (1);
}

int	count_map_size(t_map_data *map, int fd)
{
	int		ret;
	char	*line;

	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		if (!count_line_width(map, line))
			return (0);
		map->map_height++;
		free(line);
		ret = get_next_line(fd, &line);
	}
	if (ret == -1)
		return (error_custom("there was an error in get_next_line", 0));
	if (!map->map_height || !map->map_width)
		return (error_custom("wrongly formatted or empty map", 0));
	free(line);
	close(fd);
	return (1);
}
