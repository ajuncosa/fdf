/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 14:57:13 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/07 20:09:49 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	error_custom(char *message, int ret)
{
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	return (ret);
}

int	error_message(int ret)
{
	perror("Error");
	return (ret);
}

void	free_string_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_map_array(t_map_data *map)
{
	int	i;

	i = 0;
	while (i < map->map_height)
	{
		free(map->map_array[i]);
		i++;
	}
	free(map->map_array);
}

void	exit_fdf(t_data *data)
{
	mlx_destroy_image(data->mlx.ptr, data->img.ptr);
	if (data->mlx.window)
		mlx_destroy_window(data->mlx.ptr, data->mlx.window);
	free_map_array(&data->map);
	free(data->map.color_array);
	exit(0);
}
