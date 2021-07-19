/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 20:15:53 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/19 13:11:00 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <lines.h>

static t_color	calculate_color_in_gradient(t_color color1, t_color color2,
	float position)
{
	t_color	color;
	int		mixed_red;
	int		mixed_green;
	int		mixed_blue;

	mixed_red = color1.r * (1 - position) + color2.r * position;
	mixed_green = color1.g * (1 - position) + color2.g * position;
	mixed_blue = color1.b * (1 - position) + color2.b * position;
	color = color_create_rgb(mixed_red, mixed_green, mixed_blue);
	return (color);
}

// SMALL POSITIVE SLOPE: y1 < y2, dy < dx
void	bresenham_small_positive_slope(t_img_data *img,
	t_coordinates coordinates, t_color color1, t_color color2)
{
	int			x;
	int			y;
	t_bresenham	bresen_vars;

	y = coordinates.y1;
	x = coordinates.x1;
	bresen_vars.dx = coordinates.x2 - coordinates.x1;
	bresen_vars.dy = coordinates.y2 - coordinates.y1;
	bresen_vars.slope_error = 0;
	while (x <= coordinates.x2)
	{
		bresen_vars.position = (x - coordinates.x1) / bresen_vars.dx;
		bresen_vars.color = calculate_color_in_gradient(color1, color2,
				bresen_vars.position);
		my_mlx_pixel_put(img, x, y, bresen_vars.color.hex);
		bresen_vars.slope_error += bresen_vars.dy;
		if ((bresen_vars.slope_error << 1) >= bresen_vars.dx)
		{
			y++;
			bresen_vars.slope_error -= bresen_vars.dx;
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
	int			x;
	int			y;
	t_bresenham	bresen_vars;

	y = coordinates.y1;
	x = coordinates.x1;
	bresen_vars.dx = coordinates.x2 - coordinates.x1;
	bresen_vars.dy = coordinates.y2 - coordinates.y1;
	bresen_vars.slope_error = 0;
	while (y <= coordinates.y2)
	{
		bresen_vars.position = (y - coordinates.y1) / bresen_vars.dy;
		bresen_vars.color = calculate_color_in_gradient(color1, color2,
				bresen_vars.position);
		my_mlx_pixel_put(img, x, y, bresen_vars.color.hex);
		bresen_vars.slope_error += bresen_vars.dx;
		if ((bresen_vars.slope_error << 1) >= bresen_vars.dy)
		{
			x++;
			bresen_vars.slope_error -= bresen_vars.dy;
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
	int			x;
	int			y;
	t_bresenham	bresen_vars;

	y = coordinates.y1;
	x = coordinates.x1;
	bresen_vars.dx = coordinates.x2 - coordinates.x1;
	bresen_vars.dy = coordinates.y2 - coordinates.y1;
	bresen_vars.slope_error = 0;
	while (x <= coordinates.x2)
	{
		bresen_vars.position = (x - coordinates.x1) / bresen_vars.dx;
		bresen_vars.color = calculate_color_in_gradient(color1, color2,
				bresen_vars.position);
		my_mlx_pixel_put(img, x, y, bresen_vars.color.hex);
		bresen_vars.slope_error += bresen_vars.dy;
		if ((bresen_vars.slope_error << 1) <= -bresen_vars.dx)
		{
			y--;
			bresen_vars.slope_error += bresen_vars.dx;
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
** Swap colours in colour gradient, because when calculating position (number
** between 0 and 1 to calculate de proportion of colours), it goes from 1 to 0
** instead of 0 to 1 (because initial y - y2 is dy).
*/
void	bresenham_large_negative_slope(t_img_data *img,
	t_coordinates coordinates, t_color color1, t_color color2)
{
	int			x;
	int			y;
	t_bresenham	bresen_vars;

	y = coordinates.y1;
	x = coordinates.x1;
	bresen_vars.dx = coordinates.x2 - coordinates.x1;
	bresen_vars.dy = coordinates.y2 - coordinates.y1;
	bresen_vars.dy = -bresen_vars.dy;
	bresen_vars.slope_error = 0;
	while (y >= coordinates.y2)
	{
		bresen_vars.position = (y - coordinates.y2) / bresen_vars.dy;
		bresen_vars.color = calculate_color_in_gradient(color2, color1,
				bresen_vars.position);
		my_mlx_pixel_put(img, x, y, bresen_vars.color.hex);
		bresen_vars.slope_error += bresen_vars.dx;
		if ((bresen_vars.slope_error << 1) >= bresen_vars.dy)
		{
			x++;
			bresen_vars.slope_error -= bresen_vars.dy;
		}
		y--;
	}
}
