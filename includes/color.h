/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 12:14:09 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/19 12:47:50 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
	unsigned int	hex;
}					t_color;

t_color	color_create_rgb(int r, int g, int b);
t_color	color_create_hex(int hex);

#endif
