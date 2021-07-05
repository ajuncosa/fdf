/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:27:14 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/05 17:27:30 by ajuncosa         ###   ########.fr       */
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