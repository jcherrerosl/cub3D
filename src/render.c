/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiki <aloiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:09:34 by juanherr          #+#    #+#             */
/*   Updated: 2025/06/07 14:33:03 by aloiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color; 
}

void	draw_tile(t_img *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_TILE)
	{
		j = 0;
		while (j < MINIMAP_TILE)
		{
			draw_pixel(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

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

void	draw_player_circle(t_game *game, int center_x, int center_y, int radius,
		int color)
{
	int	dx;
	int	dy;

	dy = -radius;
	while (dy <= radius)
	{
		dx = -radius;
		while (dx <= radius)
		{
			if (dx * dx + dy * dy <= radius * radius)
				draw_pixel(&game->img, center_x + dx, center_y + dy, color);
			dx++;
		}
		dy++;
	}
}

void	draw_fov_cone(t_game *game, int px, int py, double angle, double fov,
		int length, int color)
{
	int		i;
	double	start_angle;
	double	ray_angle;
	int		steps;
	int		x;
	int		y;
	int		j;

	start_angle = angle - (fov / 2.0);
	steps = 50;
	i = 0;
	while (i < steps)
	{
		ray_angle = start_angle + (fov * i / steps);
		j = 0;
		while (j < length)
		{
			x = px + cos(ray_angle) * j;
			y = py + sin(ray_angle) * j;
			draw_pixel(&game->img, x, y, color);
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
	draw_player_circle(game, px, py, 3, 0xFF0000);
	draw_fov_cone(game, px, py, game->settings.player_angle, FOV, 15, 0x00FFFF);
}
