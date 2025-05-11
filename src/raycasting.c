/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:22:51 by juanherr          #+#    #+#             */
/*   Updated: 2025/05/11 21:59:50 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_column(t_game *game, int x, int wall_height, int color)
{
	int	y;
	int	end;

	y = (WIN_HEIGHT / 2) - (wall_height / 2);
	end = y + wall_height;
	if (y < 0)
		y = 0;
	if (end > WIN_HEIGHT)
		end = WIN_HEIGHT;
	while (y < end)
	{
		draw_pixel(&game->img, x, y, color);
		y++;
	}
}

double	cast_single_ray(t_game *game, double ray_angle)
{
	double	ray_x;
	double	ray_y;
	double	distance;
	double	px;
	double	py;
	int		map_x;
	int		map_y;

	distance = 0;
	px = game->settings.player_x + 0.5;
	py = game->settings.player_y + 0.5;
	while (1)
	{
		ray_x = px + cos(ray_angle) * distance;
		ray_y = py + sin(ray_angle) * distance;
		map_x = (int)ray_x;
		map_y = (int)ray_y;
		if (map_y < 0 || map_x < 0 || !game->settings.map[map_y]
			|| map_x >= (int)ft_strlen(game->settings.map[map_y])
			|| game->settings.map[map_y][map_x] == '1')
			break ;
		distance += STEP;
	}
	return (distance);
}

void	cast_rays(t_game *game)
{
	int		x;
	double	ray_angle;
	double	player_angle;
	double	ray_step;
	double	distance;
	int		wall_height;

	player_angle = game->settings.player_angle;
	ray_step = (FOV) / WIN_WIDTH;
	ray_angle = player_angle - (FOV / 2);
	x = 0;
	while (x < WIN_WIDTH)
	{
		distance = cast_single_ray(game, ray_angle);
		distance *= cos(ray_angle - player_angle); // Corrección de "fish-eye"
		wall_height = (int)(WIN_HEIGHT / distance);
		if (wall_height > WIN_HEIGHT)
			wall_height = WIN_HEIGHT;
		draw_column(game, x, wall_height, 0xAAAAAA);
		ray_angle += ray_step;
		x++;
	}
}
