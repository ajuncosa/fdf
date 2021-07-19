/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 17:10:42 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/19 15:04:02 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../minilibx/mlx.h"
# include <libft.h>
# include <color.h>
# include <stdio.h>
# define SCREEN_WIDTH 2000
# define SCREEN_HEIGHT 1200
//# define SCREEN_WIDTH 1280
//# define SCREEN_HEIGHT 680

typedef struct s_img_data
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img_data;

typedef struct s_mlx
{
	void	*ptr;
	void	*window;
}			t_mlx;

typedef struct s_map_data
{
	int	**map_array;
	int	*color_array;
	int	map_width;
	int	map_height;
}		t_map_data;

typedef struct s_traslation
{
	int	x;
	int	y;
}		t_traslation;

typedef struct s_draw
{
	float			x;
	float			y;
	float			z;
	float			initial_x;
	float			initial_y;
	float			x_inc;
	float			y_inc;
	float			angle;
	int				margin;
	float			altitude;
	float			edge_length;
	int				color;
	t_traslation	traslation;
}					t_draw;

typedef struct s_node
{
	int		x;
	int		y;
	t_color	color;
}			t_node;

typedef struct s_data
{
	t_img_data	img;
	t_map_data	map;
	t_mlx		mlx;
	t_draw		draw;
}				t_data;

/* Main functions */
int				count_map_size(t_map_data *map, int fd);
int				parse_map(t_map_data *map, const char *map_file);
int				draw_map(t_data *data);

/* Draw map auxiliary functions */
void			clear_map_from_image(t_img_data *img);
void			create_array_of_nodes(t_draw *draw, t_map_data map,
					t_node *nodes);

/* Utils */
void			my_mlx_pixel_put(t_img_data *img,
					int x, int y, unsigned int color);
int				get_index(int x, int y, int width);

/* Errors and frees */
int				error_custom(char *message, int ret);
int				error_message(int ret);
void			free_string_array(char **str);
void			free_map_array(t_map_data *map);
void			exit_fdf(t_data *data);

#endif
