/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:26:11 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/06 15:29:01 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/*
	Explanation of a, b, c and d variables for determine_starting_position():
                                z axis
         					    |
                                |
                                |
                       ____a____|________b__________
                      |  30º (  ^   ) 30º           |
                      |      /     \                |
                     d|    /         \              |
                      |  /             \            |c
                       <                 \          |
                     /   \                 \        |
                   /       \                 \      |
                 /   	     \                 \    |
               /     	       \                 \  |
             /                   \                 >
           /  					   \             /   \
         /    					     \         /       \
y axis /       						   \     /           \ x axis
            						      v

*/

void	determine_starting_position(t_draw *draw, t_map_data map)
{
	float	drawing_width; 
	float	drawing_height;
	float	a;
	float	b;
	float	c;
	float	d;
	//int		margin;

	a = cos(draw->angle) * map.map_height;
	b = cos(draw->angle) * map.map_width;
	c = sin(draw->angle) * map.map_width;
	d = sin(draw->angle) * map.map_height;
	drawing_width = a + b;
	drawing_height = c + d;
	//margin = 10;
	
//asumiendo que drawing_width > drawing_height:
float	scale = SCREEN_WIDTH / drawing_width;
draw->initial_x = a * scale;
float suma = map.map_height + map.map_width;
float div = drawing_width / suma;
printf("%f, %f, %f\n", drawing_width, suma, div);
draw->edge_length = div / cos(draw->angle);

/*	//TODO: si el array tiene más números que px tiene la pantalla
	if (drawing_width < SCREEN_WIDTH && drawing_height < SCREEN_HEIGHT)
	{
		if (drawing_width >= drawing_height) // FIXME: el drawing_width siempre es mayor que el drawing_height creo???
			draw->edge_length = SCREEN_WIDTH / (drawing_width);
		else
			draw->edge_length = SCREEN_HEIGHT / drawing_height;
	}*/
	printf("drawing w: %f, drawing h: %f\n", drawing_width, drawing_height);
	printf("a: %f, map h: %d\n", a, map.map_height);
	//draw->initial_x = a * draw->edge_length;
	draw->initial_y = 0;
}

void	draw_map(t_img_data *img, t_map_data map)
{
	int		i;
	int		j;
	int		altitude;
	t_draw	draw;
	t_coordinates coordinates;
	
	draw.angle = 30 * M_PI / 180;
	int	nodes[map.map_height * map.map_width][2];
	int	node = 0;
	altitude = 0;

	determine_starting_position(&draw, map);

	draw.x = draw.initial_x;
	draw.y = draw.initial_y;
	
	printf("starting point: (%d, %d), edge length: %f\n", draw.initial_x, draw.initial_y, draw.edge_length);
	draw.y_inc = sin(draw.angle) * draw.edge_length;
	draw.x_inc = cos(draw.angle) * draw.edge_length;
	i = 0;

	while (i < map.map_height)
	{
		j = 0;
		while (j < map.map_width)
		{	
			//printf("(%d, %d)\n", draw.x, draw.y);
			
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
