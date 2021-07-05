/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 17:10:42 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/05 20:25:08 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "minilibx/mlx.h"
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <math.h>
# include <stdio.h>
# define SCREEN_WIDTH 2000
# define SCREEN_HEIGHT 1200

typedef struct s_img_data
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img_data;

typedef struct s_map_data
{
	int	**map_array;
	int	map_width;
	int	map_height;
}				t_map_data;

typedef struct s_coordinates
{
	int	x1;
	int	x2;
	int	y1;
	int	y2;
}				t_coordinates;

/* Utils */
void			my_mlx_pixel_put(t_img_data *img,
					int x, int y, unsigned int color);
int				create_trgb(int t, int r, int g, int b);
t_coordinates	init_coordinates(int x1, int x2, int y1, int y2);

/* Bresenham line algorithm */
void			bresenham_line_algorithm(t_img_data *img,
					t_coordinates coordinates, unsigned int color);
void			bresenham_small_positive_slope(t_img_data *img,
					t_coordinates coordinates, unsigned int color);
void			bresenham_large_positive_slope(t_img_data *img,
					t_coordinates coordinates, unsigned int color);
void			bresenham_small_negative_slope(t_img_data *img,
					t_coordinates coordinates, unsigned int color);
void			bresenham_large_negative_slope(t_img_data *img,
					t_coordinates coordinates, unsigned int color);

/* Errors and frees */
int				error_custom(char *message, int ret);
int				error_message(int ret);
void			free_string_array(char **str);

int				parse_map(t_map_data *map, const char *map_file);

void			draw_map(t_img_data *img, t_map_data map);

#endif
