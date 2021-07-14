/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajuncosa <anajuncosa@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 11:23:03 by anajuncosa        #+#    #+#             */
/*   Updated: 2021/07/14 13:44:05 by anajuncosa       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	init_vars_for_nodes_array(t_draw *draw, float *start_line_x,
	float *start_line_y)
{
	*start_line_x = draw->initial_x;
	*start_line_y = draw->initial_y;
	draw->x = *start_line_x;
	draw->y = *start_line_y;
	draw->edge_length = draw->x_inc / cos(draw->angle);
}

static void	fill_nodes_array(t_draw *draw, int map_element, t_node *node)
{
	draw->z = map_element * draw->edge_length * draw->altitude;
	node->x = draw->x;
	node->y = draw->y - draw->z;
	node->color = color_create_hex(draw->color);
}

void	create_array_of_nodes(t_draw *draw, t_map_data map, t_node *nodes)
{
	int		i;
	int		j;
	int		node;
	float	start_line_x;
	float	start_line_y;

	init_vars_for_nodes_array(draw, &start_line_x, &start_line_y);
	i = -1;
	node = 0;
	while (++i < map.map_height)
	{
		j = -1;
		while (++j < map.map_width)
		{
			draw->color = map.color_array[get_index(j, i, map.map_width)];
			fill_nodes_array(draw, map.map_array[i][j], &nodes[node]);
			node++;
			draw->x += draw->x_inc;
			draw->y += draw->y_inc;
		}
		draw->x = start_line_x - draw->x_inc;
		draw->y = start_line_y + draw->y_inc;
		start_line_x = draw->x;
		start_line_y = draw->y;
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
