/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 17:10:42 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/16 11:51:09 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "minilibx/mlx.h"
# include "libft/libft.h"
# include <stdio.h>
# define SCREEN_WIDTH 2000
# define SCREEN_HEIGHT 1200
//# define SCREEN_WIDTH 1280
//# define SCREEN_HEIGHT 680

typedef enum e_keys
{
	ESC = 53,
	ARROW_DOWN = 125,
	ARROW_UP = 126,
	A_KEY = 0,
	S_KEY = 1,
	D_KEY = 2,
	W_KEY = 13
}	t_keys;

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

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
	unsigned int	hex;
}					t_color;

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
}		t_bresenham;

/* Utils */
void			my_mlx_pixel_put(t_img_data *img,
					int x, int y, unsigned int color);
t_coordinates	init_coordinates(int x1, int x2, int y1, int y2);
int				get_index(int x, int y, int width);
t_color			color_create_rgb(int r, int g, int b);
t_color			color_create_hex(int hex);

/* Bresenham line algorithm */
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

/* Errors and frees */
int				error_custom(char *message, int ret);
int				error_message(int ret);
void			free_string_array(char **str);
void			free_map_array(t_map_data *map);
void			exit_fdf(t_data *data);

/* Events */
int				handle_keypress(int keycode, t_data *data);
int				xbutton_close(t_data *data);
int				handle_mousepress(int button, int x, int y, t_draw *draw);

/* Draw map auxiliary functions */
void			clear_map_from_image(t_img_data *img);
void			create_array_of_nodes(t_draw *draw, t_map_data map,
					t_node *nodes);

/* Main functions */
int				count_map_size(t_map_data *map, int fd);
int				parse_map(t_map_data *map, const char *map_file);
int				draw_map(t_data *data);

#endif
