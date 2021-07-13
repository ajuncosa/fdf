/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajuncosa <anajuncosa@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 11:23:03 by anajuncosa        #+#    #+#             */
/*   Updated: 2021/07/13 16:57:33 by anajuncosa       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	create_array_of_nodes(t_draw *draw, t_map_data map, t_node *nodes)
{
	int		i;
	int		j;
	int		node;
	float	start_line_x;
	float	start_line_y;
	float	edge_length;
	int		color;

	start_line_x = draw->initial_x;
	start_line_y = draw->initial_y;
	draw->x = start_line_x;
	draw->y = start_line_y;
	edge_length = draw->x_inc / cos(draw->angle);
	i = 0;
	node = 0;
	while (i < map.map_height)
	{
		j = 0;
		while (j < map.map_width)
		{
			draw->z = map.map_array[i][j] * edge_length * draw->altitude;
			nodes[node].x = draw->x;
			nodes[node].y = draw->y - draw->z;
			color = map.color_array[get_index(j, i, map.map_width)];
			nodes[node].color = color_create_hex(color);
			node++;
			draw->x += draw->x_inc;
			draw->y += draw->y_inc;
			j++;
		}
		draw->x = start_line_x - draw->x_inc;
		draw->y = start_line_y + draw->y_inc;
		start_line_x = draw->x;
		start_line_y = draw->y;
		i++;
	}
}

void	clear_map_from_image(t_img_data *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCREEN_HEIGHT)
	{
		j = 0;
		while (j < SCREEN_WIDTH)
		{
			my_mlx_pixel_put(img, j, i, 0x000000);
			j++;
		}
		i++;
	}
}
