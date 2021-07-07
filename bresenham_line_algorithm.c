/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line_algorithm.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 19:16:15 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/07 18:30:02 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// To ensure that the line is drawn from left to right
static void	swap_line_endpoints(int *x1, int *x2, int *y1, int *y2)
{
	int	tmp;

	tmp = *x1;
	*x1 = *x2;
	*x2 = tmp;
	tmp = *y1;
	*y1 = *y2;
	*y2 = tmp;
}

void	bresenham_line_algorithm(t_img_data *img,
	t_coordinates coordinates, unsigned int color)
{
	float	dx;
	float	dy;
	float	slope;

	if (coordinates.x2 < coordinates.x1)
		swap_line_endpoints(&coordinates.x1, &coordinates.x2,
			&coordinates.y1, &coordinates.y2);
	dx = coordinates.x2 - coordinates.x1;
	dy = coordinates.y2 - coordinates.y1;
	slope = dy / dx;
	if (slope >= 0 && slope <= 1)
		bresenham_small_positive_slope(img, coordinates, color);
	else if (slope > 1)
		bresenham_large_positive_slope(img, coordinates, color);
	else if (slope < 0 && slope >= -1)
		bresenham_small_negative_slope(img, coordinates, color);
	else if (slope < -1)
		bresenham_large_negative_slope(img, coordinates, color);
}
