/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 12:44:35 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/19 13:00:46 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

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

int	handle_keypress(int keycode, t_data *data);
int	xbutton_close(t_data *data);
int	handle_mousepress(int button, int x, int y, t_draw *draw);

#endif
