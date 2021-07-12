/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajuncosa <anajuncosa@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 13:12:38 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/12 17:52:58 by anajuncosa       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == ESC)
		exit_fdf(data);
	else if (keycode == A_KEY)
		data->draw.traslation.x += 10;
	else if (keycode == D_KEY)
		data->draw.traslation.x -= 10;
	else if (keycode == W_KEY)
		data->draw.traslation.y += 10;
	else if (keycode == S_KEY)
		data->draw.traslation.y -= 10;
	else if (keycode == ARROW_UP)
		data->draw.altitude += 0.02;
	else if (keycode == ARROW_DOWN)
		data->draw.altitude -= 0.02;
	return (0);
}

int	xbutton_close(t_data *data)
{
	exit_fdf(data);
	return (0);
}

int	handle_mousepress(int button, int x, int y, t_draw *draw)
{
	y += 0;
	x += 0;
	if (button == 4)
		draw->margin -= 100;
	else if (button == 5 && draw->margin < SCREEN_WIDTH - 100)
		draw->margin += 100;
	return (0);
}
