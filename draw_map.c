/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:26:11 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/08 12:59:51 by ajuncosa         ###   ########.fr       */
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
	draw->initial_x = draw->traslation.x  + extra_space_x + (map.map_height - 1) * draw->x_inc;
	draw->initial_y = draw->traslation.y + extra_space_y;
}

static void	create_array_of_nodes(t_draw *draw, t_map_data map, t_node *nodes)
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

static void	draw_edge_lines(t_img_data *img, t_map_data map, t_node *nodes)
{
	int				node;
	int				i;
	int				j;
	t_coordinates	coordinates;
	int				next_x;
	int				next_y;

	node = 0;
	i = 0;
	j = 0;
	while (node < map.map_height * map.map_width)
	{
		if (j < map.map_height - 1)
		{
			next_y = node + map.map_width;
			coordinates = init_coordinates(nodes[node].x, nodes[next_y].x,
				nodes[node].y, nodes[next_y].y);
			bresenham_line_algorithm(img, coordinates, nodes[node].color, nodes[next_y].color);
		}
		if (i < map.map_width - 1)
		{
			next_x = node + 1;
			coordinates = init_coordinates(nodes[node].x, nodes[next_x].x,
				nodes[node].y, nodes[next_x].y);
			bresenham_line_algorithm(img, coordinates, nodes[node].color, nodes[next_x].color);
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

int	draw_map(t_data *data)
{
	t_node	*nodes;

	clear_map_from_image(&data->img);

	nodes = malloc(data->map.map_height * data->map.map_width * sizeof(t_node));
	determine_starting_position(&data->draw, data->map);
	create_array_of_nodes(&data->draw, data->map, nodes);
	draw_edge_lines(&data->img, data->map, nodes);
	free(nodes);
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.window, data->img.ptr, 0, 0);
	return (0);
}
