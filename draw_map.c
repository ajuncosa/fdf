/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajuncosa <anajuncosa@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:26:11 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/13 16:44:53 by anajuncosa       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	determine_starting_position(t_draw *draw, t_map_data map)
{
	float	map_edges_sum;
	float	extra_space_x;
	float	extra_space_y;

	draw->angle = 30 * M_PI / 180;
	map_edges_sum = map.map_width + map.map_height - 2;
	draw->x_inc = (SCREEN_WIDTH - draw->margin) / map_edges_sum;
	draw->y_inc = draw->x_inc * tan(draw->angle);
	if (draw->y_inc * map_edges_sum > SCREEN_HEIGHT)
	{
		draw->y_inc = ((SCREEN_HEIGHT - draw->margin) / map_edges_sum);
		draw->x_inc = (draw->y_inc / tan(draw->angle));
	}
	extra_space_x = (SCREEN_WIDTH - map_edges_sum * draw->x_inc) / 2;
	extra_space_y = (SCREEN_HEIGHT - map_edges_sum * draw->y_inc) / 2;
	draw->initial_x = draw->traslation.x + extra_space_x
		+ (map.map_height - 1) * draw->x_inc;
	draw->initial_y = draw->traslation.y + extra_space_y;
}

static void	draw_vertical_edge(t_img_data *img, int map_width,
	t_node *nodes, int node)
{
	int				next_y;
	t_coordinates	coordinates;

	next_y = node + map_width;
	coordinates = init_coordinates(nodes[node].x, nodes[next_y].x,
			nodes[node].y, nodes[next_y].y);
	bresenham_line_algorithm(img, coordinates, nodes[node].color,
		nodes[next_y].color);
}

static void	draw_horizontal_edge(t_img_data *img, t_node *nodes, int node)
{
	int				next_x;
	t_coordinates	coordinates;

	next_x = node + 1;
	coordinates = init_coordinates(nodes[node].x, nodes[next_x].x,
			nodes[node].y, nodes[next_x].y);
	bresenham_line_algorithm(img, coordinates, nodes[node].color,
		nodes[next_x].color);
}

static void	draw_edge_lines(t_img_data *img, t_map_data map, t_node *nodes)
{
	int	node;
	int	i;
	int	j;

	node = 0;
	i = 0;
	j = 0;
	while (node < map.map_height * map.map_width)
	{
		if (j < map.map_height - 1)
			draw_vertical_edge(img, map.map_width, nodes, node);
		if (i < map.map_width - 1)
		{
			draw_horizontal_edge(img, nodes, node);
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

int	draw_map(t_data *data)
{
	t_node	*nodes;

	clear_map_from_image(&data->img);
	nodes = malloc(data->map.map_height * data->map.map_width * sizeof(t_node));
	determine_starting_position(&data->draw, data->map);
	create_array_of_nodes(&data->draw, data->map, nodes);
	draw_edge_lines(&data->img, data->map, nodes);
	free(nodes);
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.window,
		data->img.ptr, 0, 0);
	return (0);
}
