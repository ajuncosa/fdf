/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 12:19:58 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/19 15:04:26 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINES_H
# define LINES_H

# include <color.h>

typedef struct s_coordinates
{
	int	x1;
	int	x2;
	int	y1;
	int	y2;
}		t_coordinates;

typedef struct s_bresenham
{
	float	dx;
	float	dy;
	int		slope_error;
	t_color	color;
	float	position;
}			t_bresenham;

t_coordinates	init_coordinates(int x1, int x2, int y1, int y2);
void			bresenham_line_algorithm(t_img_data *img,
					t_coordinates coordinates, t_color color1, t_color color2);
void			bresenham_small_positive_slope(t_img_data *img,
					t_coordinates coordinates, t_color color1, t_color color2);
void			bresenham_large_positive_slope(t_img_data *img,
					t_coordinates coordinates, t_color color1, t_color color2);
void			bresenham_small_negative_slope(t_img_data *img,
					t_coordinates coordinates, t_color color1, t_color color2);
void			bresenham_large_negative_slope(t_img_data *img,
					t_coordinates coordinates, t_color color1, t_color color2);

#endif
