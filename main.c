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

void	my_mlx_pixel_put(t_img_data *img, int x, int y, unsigned int color)
{
	char	*dst;
	int		memory_offset;

	memory_offset = y * img->line_length + x * (img->bits_per_pixel / 8);
	dst = img->addr + memory_offset;
	*(unsigned int *)dst = color;
}

void	swap_line_endpoints(int *x1, int *x2, int *y1, int *y2)
{
	int tmp;

	tmp = *x1;
	*x1 = *x2;
	*x2 = tmp;
	tmp = *y1;
	*y1 = *y2;
	*y2 = tmp;
}

void	bresenham_line_algorithm(t_img_data *img, int x1, int x2, int y1, int y2, unsigned int color)
{
	float	dx;
	float	dy;
	int		x;
	int		y;
	int		slope_error;
	float	slope;

	// ensure line is drawn from left to right:
	if (x2 < x1)
		swap_line_endpoints(&x1, &x2, &y1, &y2);

	//init some variables
	dx = x2 - x1;
	dy = y2 - y1;
	slope = dy / dx;
	slope_error = 0;
	y = y1;
	x = x1;

	// SMALL POSITIVE SLOPE: y1 < y2, dy < dx
	// This is the normal case:
	if (slope >= 0 && slope <= 1)
	{
		while (x <= x2)
		{
			my_mlx_pixel_put(img, x, y, color);
			slope_error += dy;
			if ((slope_error << 1) >= dx)
			{
				y++;
				slope_error -= dx;
			}
			x++;
		}
	}
	// LARGE POSITIVE SLOPE: y1 < y2, dy > dx
	// Step over y instead of x: Instead of m <- dy /dx, I calculate
	// m <- dx / dy so that it'll work for my error variable, therefore
	// all my calculations have dx and dy swapped (when compared
	// to small positive slope).
	else if (slope > 1)
	{
		while (y <= y2)
		{
			my_mlx_pixel_put(img, x, y, color);
			slope_error += dx;
			if ((slope_error << 1) >= dy)
			{
				x++;
				slope_error -= dy;
			}
			y++;
		}
	}
	// SMALL NEGATIVE SLOPE: y1 > y2, dy < dx
	// Error condition changed because of negative m (due to negative dy).
	// Error update for each step also changed due to this.
	// Decrease in y instead of increase, because y2 < y1.
	else if (slope < 0 && slope >= -1)
	{
		while (x <= x2)
		{
			my_mlx_pixel_put(img, x, y, color);
			slope_error += dy;
			if ((slope_error << 1) <= -dx)
			{
				y--;
				slope_error += dx;
			}
			x++;
		}
	}
	// LARGE NEGATIVE SLOPE: y1 > y2, dy > dx
	// Step over y instead of x (as a result, dy and dx are swapped, m <- dx / dy).
	// Because I am stepping over y, the error condition for negative slopes
	// does not work in this case, because the errors are calculated from x,
	// and x1 is always < x2. The exact same logic as large pos. slope applies
	// here, with the exeption that dy is negative and, as a result, the error
	// is negative. I needed to change dy's sign so that the error calcs would work the same.
	// Decrease in y because y2 < y1.
	else if (slope < -1)
	{
		dy = -dy;
		while (y >= y2)
		{
			my_mlx_pixel_put(img, x, y, color);
			slope_error += dx;
			if ((slope_error << 1) >= dy)
			{
				x++;
				slope_error -= dy;
			}
			y--;
		}
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
	bresenham_line_algorithm(&img, 300, 0, 50, 100, 0x00FFFFFF);
	mlx_put_image_to_window(mlx_ptr, window, img.ptr, 0, 0);
	mlx_loop(mlx_ptr);
	return (0);
}
