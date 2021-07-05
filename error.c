/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 14:57:13 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/07/05 16:38:59 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	error_custom(char *message, int ret)
{
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	return (ret);
}

int	error_message(int ret)
{
	perror("Error");
	return (ret);
}

void	free_string_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
