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

int create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_img_data *img, int x, int y, int color)
{
	char	*dst;
	int		memory_offset;

	memory_offset = y * img->line_length + x * (img->bits_per_pixel / 8);
	dst = img->addr + memory_offset;
	*(unsigned int *)dst = color;
}

void	bresenham_line_algorithm(t_img_data *img, int x1, int x2, int y1, int y2)
{
	int	m;
	int slope_error;
	int	x;
	int	y;

	m = 2 * (y2 - y1);
	slope_error = m - (x2 - x1);
	x = x1;
	y = y1;
	while (x <= x2)
	{
		my_mlx_pixel_put(img, x, y, 0x00FF0000);
		slope_error += m;
		if (slope_error >= 0)
		{
			y++;
			slope_error -= 2 * (x2 - x1);
		}
		x++;
	}
}

int main()
{
	void   		*mlx_ptr;
	void   		*window;
	t_img_data	img;

	mlx_ptr = mlx_init();
	window = mlx_new_window(mlx_ptr, 600, 400, "hola");
	img.ptr = mlx_new_image(mlx_ptr, 600, 400);
	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_length, &img.endian);
	bresenham_line_algorithm(&img, 5, 100, 100, 5);
	mlx_put_image_to_window(mlx_ptr, window, img.ptr, 0, 0);
	mlx_loop(mlx_ptr);
	return (0);
}
