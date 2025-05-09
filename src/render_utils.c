/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:11:26 by juanherr          #+#    #+#             */
/*   Updated: 2025/05/09 12:12:05 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	draw_background(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	int color_ceiling = rgb_to_int(
		game->settings.ceiling_rgb[0],
		game->settings.ceiling_rgb[1],
		game->settings.ceiling_rgb[2]);
	int color_floor = rgb_to_int(
		game->settings.floor_rgb[0],
		game->settings.floor_rgb[1],
		game->settings.floor_rgb[2]);
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
			draw_pixel(&game->img, x++, y, color_ceiling);
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
			draw_pixel(&game->img, x++, y, color_floor);
		y++;
	}
}
