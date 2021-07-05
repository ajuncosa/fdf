/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 17:10:42 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/05 17:27:46 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "minilibx/mlx.h"
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <math.h>
# include <stdio.h>
# define SCREEN_WIDTH 2560
# define SCREEN_HEIGHT 1440

typedef struct	s_img_data
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img_data;

typedef struct	s_map_data
{
	int	**map_array;
	int map_width;
	int	map_height;
}				t_map_data;

void	my_mlx_pixel_put(t_img_data *img, int x, int y, unsigned int color);
int		create_trgb(int t, int r, int g, int b);
void	bresenham_line_algorithm(t_img_data *img, int x1, int x2, int y1, int y2, unsigned int color);
int		error_custom(char *message, int ret);
int		error_message(int ret);
void	free_string_array(char **str);

int		parse_map(t_map_data *map, char *map_file);

void	draw_map(t_img_data *img, t_map_data map);

#endif
