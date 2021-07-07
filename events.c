/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 13:12:38 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/07 13:14:23 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == 53)
		exit_fdf(data);
	return (0);
}

int	xbutton_close(t_data *data)
{
	exit_fdf(data);
	return (0);
}
