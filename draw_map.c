/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:26:11 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/05 20:14:13 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_map(t_img_data *img, t_map_data map)
{
	int	i;
	int	j;
	int	x;
	int	y;
	float	y_inc;
	float	x_inc;
	int	initial_x;
	int	initial_y;
	int	edge_length = 10;
	float angle = 30 * M_PI / 180;
	int	nodes[map.map_height * map.map_width][2];
	int	node = 0;
	int	z;
	t_coordinates coordinates;

	initial_x = SCREEN_WIDTH / 2;
	initial_y = 0;
	x = initial_x;
	y = initial_y;
	y_inc = sin(angle) * edge_length;
	x_inc = cos(angle) * edge_length;
	i = 0;
	while (i < map.map_height)
	{
		j = 0;
		while (j < map.map_width)
		{
			z = map.map_array[i][j] * 5;
			nodes[node][0] = x;
			nodes[node][1] = y - z;
			node++;
			x += x_inc;
			y += y_inc;
			j++;
		}
		x = initial_x - x_inc;
		y = initial_y + y_inc;
		initial_x = x;
		initial_y = y;
		i++;
	}
	node = 0;
	i = 0;
	j = 0;
	while (node < map.map_height * map.map_width)
	{
		if (j < map.map_height - 1)
		{
			coordinates = init_coordinates(nodes[node][0], nodes[node + map.map_width][0], nodes[node][1], nodes[node + map.map_width][1]);
			bresenham_line_algorithm(img, coordinates, 0x00FFFFFF);
		}
		if (i < map.map_width - 1)
		{
			coordinates = init_coordinates(nodes[node][0], nodes[node + 1][0], nodes[node][1], nodes[node + 1][1]);
			bresenham_line_algorithm(img, coordinates, 0x00FFFFFF);
			i++;
		}
		else
		{
			i = 0;
			j++;
		}
		node++;
	}
}
