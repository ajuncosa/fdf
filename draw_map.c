/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:26:11 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/07 16:57:52 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

//TODO: qué hacer si el array tiene más números que px tiene la pantalla
void	determine_starting_position(t_draw *draw, t_map_data map)
{
	int	map_sides_edges_sum;
	int	extra_space_x;
	int	extra_space_y;

	draw->margin = 100;
	draw->angle = 30 * M_PI / 180;
	map_sides_edges_sum = map.map_width + map.map_height - 2; // para contar sólo los huecos entre puntos en vez de los puntos
	draw->x_inc = (int)((SCREEN_WIDTH - draw->margin) / map_sides_edges_sum);
	draw->y_inc = (int)(draw->x_inc * tan(draw->angle));
	if (draw->y_inc * map_sides_edges_sum > SCREEN_HEIGHT)
	{
		draw->y_inc = (int)((SCREEN_HEIGHT - draw->margin) / map_sides_edges_sum);
		draw->x_inc = (int)(draw->y_inc / tan(draw->angle));
	}
	extra_space_x = (SCREEN_WIDTH - map_sides_edges_sum * draw->x_inc) / 2;  // para centrar
	extra_space_y = (SCREEN_HEIGHT - map_sides_edges_sum * draw->y_inc) / 2;
	draw->initial_x = extra_space_x + (map.map_height - 1) * draw->x_inc;
	draw->initial_y = extra_space_y;
}

void	draw_map(t_img_data *img, t_map_data map)
{
	int		i;
	int		j;
	float	altitude;
	t_draw	draw;
	t_coordinates coordinates;
	int	nodes[map.map_height * map.map_width][2];
	int	node = 0;

	determine_starting_position(&draw, map);
	altitude = 5;
	draw.x = draw.initial_x;
	draw.y = draw.initial_y;
	i = 0;
	while (i < map.map_height)
	{
		j = 0;
		while (j < map.map_width)
		{	
			draw.z = map.map_array[i][j] * altitude;
			nodes[node][0] = draw.x;
			nodes[node][1] = draw.y - draw.z;
			node++;
			draw.x += draw.x_inc;
			draw.y += draw.y_inc;
			j++;
		}
		draw.x = draw.initial_x - draw.x_inc;
		draw.y = draw.initial_y + draw.y_inc;
		draw.initial_x = draw.x;
		draw.initial_y = draw.y;
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
