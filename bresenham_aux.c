/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 20:15:53 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/08 13:50:23 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// SMALL POSITIVE SLOPE: y1 < y2, dy < dx
void	bresenham_small_positive_slope(t_img_data *img,
	t_coordinates coordinates, t_color color1, t_color color2)
{
	int		x;
	int		y;
	float	dx;
	float	dy;
	int		slope_error;
	t_color	color;
	float	position;

	y = coordinates.y1;
	x = coordinates.x1;
	dx = coordinates.x2 - coordinates.x1;
	dy = coordinates.y2 - coordinates.y1;
	slope_error = 0;
	while (x <= coordinates.x2)
	{
		position = (x - coordinates.x1) / dx;
		color = color_create_rgb(color1.r * (1 - position) + color2.r * position, color1.g * (1 - position) + color2.g * position, color1.b * (1 - position) + color2.b * position);
		my_mlx_pixel_put(img, x, y, color.hex);
		slope_error += dy;
		if ((slope_error << 1) >= dx)
		{
			y++;
			slope_error -= dx;
		}
		x++;
	}
}

/*
** LARGE POSITIVE SLOPE: y1 < y2, dy > dx
** Step over y instead of x: instead of m <- dy /dx, I calculate m <- dx / dy
** so that it'll work for my error variable, therefore all my calculations have
** dx and dy swapped (when compared to small positive slope).
*/
void	bresenham_large_positive_slope(t_img_data *img,
	t_coordinates coordinates, t_color color1, t_color color2)
{
	int		x;
	int		y;
	float	dx;
	float	dy;
	int		slope_error;
	t_color	color;
	float	position;

	y = coordinates.y1;
	x = coordinates.x1;
	dx = coordinates.x2 - coordinates.x1;
	dy = coordinates.y2 - coordinates.y1;
	slope_error = 0;
	while (y <= coordinates.y2)
	{
		position = (y - coordinates.y1) / dy;
		color = color_create_rgb(color1.r * (1 - position) + color2.r * position, color1.g * (1 - position) + color2.g * position, color1.b * (1 - position) + color2.b * position);
		my_mlx_pixel_put(img, x, y, color.hex);
		slope_error += dx;
		if ((slope_error << 1) >= dy)
		{
			x++;
			slope_error -= dy;
		}
		y++;
	}
}

/*
** SMALL NEGATIVE SLOPE: y1 > y2, dy < dx
** Error condition changed because of negative m (due to negative dy).
** Error update for each step also changed due to this.
** Decrease in y instead of increase, because y2 < y1.
*/
void	bresenham_small_negative_slope(t_img_data *img,
	t_coordinates coordinates, t_color color1, t_color color2)
{
	int		x;
	int		y;
	float	dx;
	float	dy;
	int		slope_error;
	t_color	color;
	float	position;

	y = coordinates.y1;
	x = coordinates.x1;
	dx = coordinates.x2 - coordinates.x1;
	dy = coordinates.y2 - coordinates.y1;
	slope_error = 0;
	while (x <= coordinates.x2)
	{
		position = (x - coordinates.x1) / dx;
		color = color_create_rgb(color1.r * (1 - position) + color2.r * position, color1.g * (1 - position) + color2.g * position, color1.b * (1 - position) + color2.b * position);

		my_mlx_pixel_put(img, x, y, color.hex);
		slope_error += dy;
		if ((slope_error << 1) <= -dx)
		{
			y--;
			slope_error += dx;
		}
		x++;
	}
}

/*
** LARGE NEGATIVE SLOPE: y1 > y2, dy > dx
** Step over y instead of x (as a result, dy and dx are swapped, m <- dx / dy).
** Because I am stepping over y, the error condition for negative slopes does
** not work in this case, because the errors are calculated from x, and x1 is
** always < x2. The exact same logic as large pos. slope applies here, with
** the exeption that dy is negative and, as a result, the error is negative. I
** needed to change dy's sign so that the error calcs would work the same.
** Decrease in y because y2 < y1.
*/
void	bresenham_large_negative_slope(t_img_data *img,
	t_coordinates coordinates, t_color color1, t_color color2)
{
	int		x;
	int		y;
	float	dx;
	float	dy;
	int		slope_error;
	t_color	color;
	float	position;

	y = coordinates.y1;
	x = coordinates.x1;
	dx = coordinates.x2 - coordinates.x1;
	dy = coordinates.y2 - coordinates.y1;
	dy = -dy;
	slope_error = 0;
	while (y >= coordinates.y2)
	{
		position = (y - coordinates.y1) / dy;
		color = color_create_rgb(color1.r * (1 - position) + color2.r * position, color1.g * (1 - position) + color2.g * position, color1.b * (1 - position) + color2.b * position);

		my_mlx_pixel_put(img, x, y, color.hex);
		slope_error += dx;
		if ((slope_error << 1) >= dy)
		{
			x++;
			slope_error -= dy;
		}
		y--;
	}
}
