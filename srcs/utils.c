/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:27:14 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/19 13:12:18 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <lines.h>

void	my_mlx_pixel_put(t_img_data *img, int x, int y, unsigned int color)
{
	char	*dst;
	int		memory_offset;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	memory_offset = y * img->line_length + x * (img->bits_per_pixel / 8);
	dst = img->addr + memory_offset;
	*(unsigned int *)dst = color;
}

t_coordinates	init_coordinates(int x1, int x2, int y1, int y2)
{
	t_coordinates	coordinates;

	coordinates.x1 = x1;
	coordinates.x2 = x2;
	coordinates.y1 = y1;
	coordinates.y2 = y2;
	return (coordinates);
}

int	get_index(int x, int y, int width)
{
	return (y * width + x);
}

t_color	color_create_rgb(int r, int g, int b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.hex = r << 16 | g << 8 | b;
	return (color);
}

t_color	color_create_hex(int hex)
{
	t_color	color;

	color.hex = hex;
	color.r = (hex & (0xFF << 16)) >> 16;
	color.g = (hex & (0xFF << 8)) >> 8;
	color.b = hex & 0xFF;
	return (color);
}
