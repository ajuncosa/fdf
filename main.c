/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 18:16:25 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/06 10:54:00 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int main(int argc, char **argv)
{
	void   		*mlx_ptr;
	void   		*window;
	t_img_data	img;
	t_map_data	map;

	if (argc != 2)
		return (error_custom("Error: wrong number of arguments", 1));
	if (!parse_map(&map, argv[1]))
		return (1);
	/*int i = 0;
	while (i < map.map_height)
	{
		int j = 0;
		while (j < map.map_width)
		{
			printf("%d ", map.map_array[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}*/

	mlx_ptr = mlx_init();
	window = mlx_new_window(mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "hola");
	img.ptr = mlx_new_image(mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_length, &img.endian);
	draw_map(&img, map);
	mlx_put_image_to_window(mlx_ptr, window, img.ptr, 0, 0);
	mlx_loop(mlx_ptr);
	int i = 0;
	while (i < map.map_height)
	{
		free(map.map_array[i]);
		i++;
	}
	free(map.map_array);
	return (0);
}
