/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:09:34 by juanherr          #+#    #+#             */
/*   Updated: 2025/06/10 11:10:28 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map(t_game *game)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (game->settings.map && game->settings.map[y])
	{
		x = 0;
		while (game->settings.map[y][x])
		{
			if (game->settings.map[y][x] == '1')
				color = COLOR_WALL;
			else
				color = COLOR_FLOOR;
			draw_tile(&game->img, x * TILE_SIZE, y * TILE_SIZE, color);
			x++;
		}
		y++;
	}
	draw_tile(&game->img, game->settings.player_x * TILE_SIZE + TILE_SIZE / 4,
		game->settings.player_y * TILE_SIZE + TILE_SIZE / 4, COLOR_PLAYER);
}

void	draw_player_circle(t_game *g, int color)
{
	int	dx;
	int	dy;

	g->center_x = g->settings.player_x * MINIMAP_TILE;
	g->center_y = g->settings.player_y * MINIMAP_TILE;
	g->radius = 3;
	dy = -(g->radius);
	while (dy <= g->radius)
	{
		dx = -(g->radius);
		while (dx <= g->radius)
		{
			if (dx * dx + dy * dy <= g->radius * g->radius)
				draw_pixel(&g->img, g->center_x + dx, g->center_y + dy, color);
			dx++;
		}
		dy++;
	}
}

void	draw_fov_cone(t_game *g, int px, int py, int length)
{
	int		i;
	int		steps;
	int		x;
	int		y;
	int		j;

	g->angle = g->settings.player_angle;
	g->fov = FOV;
	g->start_angle = g->angle - (g->fov / 2.0);
	steps = 50;
	i = 0;
	while (i < steps)
	{
		g->ray_angle = g->start_angle + (g->fov * i / steps);
		j = 0;
		while (j < length)
		{
			x = px + cos(g->ray_angle) * j;
			y = py + sin(g->ray_angle) * j;
			draw_pixel(&g->img, x, y, COLOR_CONE);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int	x;
	int	y;
	int	color;
	int	px;
	int	py;

	y = 0;
	while (game->settings.map && game->settings.map[y])
	{
		x = 0;
		while (game->settings.map[y][x])
		{
			if (game->settings.map[y][x] == '1')
				color = COLOR_WALL;
			else
				color = COLOR_FLOOR;
			draw_tile(&game->img, x * MINIMAP_TILE, y * MINIMAP_TILE, color);
			x++;
		}
		y++;
	}
	px = game->settings.player_x * MINIMAP_TILE;
	py = game->settings.player_y * MINIMAP_TILE;
	draw_player_circle(game, COLOR_PLAYER);
	draw_fov_cone(game, px, py, 15);
}
