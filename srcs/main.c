/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 18:16:25 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/19 13:07:01 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <events.h>

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == ESC)
		exit_fdf(data);
	return (0);
}

int	xbutton_close(t_data *data)
{
	exit_fdf(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (error_custom("Error: wrong number of arguments", 1));
	if (!parse_map(&data.map, argv[1]))
		return (1);
	data.draw.altitude = 0.3;
	data.draw.margin = 100;
	data.draw.traslation.x = 0;
	data.draw.traslation.y = 0;
	data.mlx.ptr = mlx_init();
	data.mlx.window = mlx_new_window(data.mlx.ptr,
			SCREEN_WIDTH, SCREEN_HEIGHT, "FdF");
	data.img.ptr = mlx_new_image(data.mlx.ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.ptr, &data.img.bits_per_pixel,
			&data.img.line_length, &data.img.endian);
	mlx_loop_hook(data.mlx.ptr, draw_map, &data);
	mlx_hook(data.mlx.window, 2, 0L, handle_keypress, &data);
	mlx_hook(data.mlx.window, 17, 0L, xbutton_close, &data);
	mlx_loop(data.mlx.ptr);
	return (0);
}
