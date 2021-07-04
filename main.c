/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 18:16:25 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/02 18:25:06 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"
#include <math.h>

int create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_img_data *img, int x, int y, unsigned int color)
{
	char	*dst;
	int		memory_offset;

	memory_offset = y * img->line_length + x * (img->bits_per_pixel / 8);
	dst = img->addr + memory_offset;
	*(unsigned int *)dst = color;
}

// en esta funcion encuentro dónde deben estar los puntos (nodos), para luego unirlos. Falta calcular los que tengan z > 0
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
	int	edge_length = 50;
	float angle = 30 * M_PI / 180;
	int	nodes[map.map_height * map.map_width][2];
	int	node = 0;

	i = 0;
	initial_x = 200;
	initial_y = 200;
	x = initial_x;
	y = initial_y;
	y_inc = sin(angle) * edge_length;
	x_inc = cos(angle) * edge_length;
	while (i < map.map_height)
	{
		j = 0;
		while (j < map.map_width)
		{
			//printf("(%d, %d)\n", x, y);
			my_mlx_pixel_put(img, x, y, 0x00FFFFFF);
			nodes[node][0] = x;
			nodes[node][1] = y;
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
	while (node < map.map_height * map.map_width)
	{
		printf("(%d, %d)\n", nodes[node][0], nodes[node][1]);
		node++;
	}
}

int main()
{
	void   		*mlx_ptr;
	void   		*window;
	t_img_data	img;
	t_map_data	map;
	map.map_height = 3;
	map.map_width = 3;
	/*int	array[map.map_height][map.map_width] = {
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	};*/

	mlx_ptr = mlx_init();
	window = mlx_new_window(mlx_ptr, 600, 400, "hola");
	img.ptr = mlx_new_image(mlx_ptr, 600, 400);
	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_length, &img.endian);
	draw_map(&img, map);
	//bresenham_line_algorithm(&img, 50, 100, 300, 0, 0x00FFFFFF);
	mlx_put_image_to_window(mlx_ptr, window, img.ptr, 0, 0);
	mlx_loop(mlx_ptr);
	return (0);
}
