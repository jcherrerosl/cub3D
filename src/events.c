/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:30:13 by juanherr          #+#    #+#             */
/*   Updated: 2025/05/08 14:30:56 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_handler(int key, t_img *img)
{
	if (key == KEY_ESC)
	{
		close_window(img);
	}
	return (0);
}

int	close_window(t_img *img)
{
	ft_printf("Exiting game\n");
	mlx_destroy_window(img->mlx, img->win);
	exit(0);
}
