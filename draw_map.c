/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:26:11 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/07 10:58:28 by ajuncosa         ###   ########.fr       */
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
	//float	drawing_width; 
	//float	drawing_height;
	//float	a;
	//float	b;
	//float	c;
	//float	d;
	int		margin;

	/*a = cos(draw->angle) * map.map_height;
	b = cos(draw->angle) * map.map_width;
	c = sin(draw->angle) * map.map_width;
	d = sin(draw->angle) * map.map_height;
	drawing_width = a + b;
	drawing_height = c + d;*/
	margin = 100;


//asumiendo que tengo que ajustarlo de ancho pero no de alto
	float	map_sides_sum = map.map_width + map.map_height;
	draw->x_inc = (SCREEN_WIDTH - margin) / (map_sides_sum - 2); // para contar sólo los huecos entre puntos en vez de los puntos
	draw->y_inc = draw->x_inc * tan(draw->angle);

	//TODO: qué hacer si el array tiene más números que px tiene la pantalla
	/*if (drawing_width < SCREEN_WIDTH && drawing_height < SCREEN_HEIGHT)
	{
		if (drawing_width >= drawing_height) // FIXME: el drawing_width siempre es mayor que el drawing_height creo??? cambiar esta condición por si la forma de la pantalla es otra, aunque sea más ancho que largo, tal vez tenga que tener en cuenta la altura envez de la anchura
			draw->edge_length = SCREEN_WIDTH / sum;
		else
			draw->edge_length = SCREEN_HEIGHT / drawing_height;
	}*/
	//printf("drawing w: %f, drawing h: %f\n", drawing_width, drawing_height);
	//printf("a: %f, map h: %d\n", a, map.map_height);
	draw->initial_x = margin / 2 + round((map.map_height - 1) * draw->x_inc);
	draw->initial_y = margin / 2;
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
	altitude = 5;

	determine_starting_position(&draw, map);

	draw.x = draw.initial_x;
	draw.y = draw.initial_y;
	
	//printf("starting point: (%d, %d), edge length: %f\n", draw.initial_x, draw.initial_y, draw.edge_length);
	//draw.y_inc = sin(draw.angle) * draw.edge_length;
	//draw.x_inc = cos(draw.angle) * draw.edge_length;
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
