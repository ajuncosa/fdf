/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:27:14 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/05 20:15:22 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

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
