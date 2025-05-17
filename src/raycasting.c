/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiki <aloiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:22:51 by juanherr          #+#    #+#             */
/*   Updated: 2025/05/17 17:12:22 by aloiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_column(t_game *game, int x, int wall_height, int color)
{
	int	y;
	int	end;

	y = (WIN_HEIGHT / 2) - (wall_height / 2) + game->camera->vert_offset;
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

double	cast_single_ray(t_game *game, double ray_angle, double *ray_x,
		double *ray_y, int *side)
{
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
		*ray_x = px + cos(ray_angle) * distance;
		*ray_y = py + sin(ray_angle) * distance;
		map_x = (int)(*ray_x);
		map_y = (int)(*ray_y);
		if (map_y < 0 || map_x < 0 || !game->settings.map[map_y]
			|| map_x >= (int)ft_strlen(game->settings.map[map_y])
			|| game->settings.map[map_y][map_x] == '1')
		{
			if (fabs((*ray_x - px)) > fabs((*ray_y - py))) //valor absoluto
			{
				*side = 0; // impacto vertical (este/oeste)
				if (cos(ray_angle) > 0)
					map_x = (int)(*ray_x);
				else
					map_x = (int)(*ray_x) + 1;
				*ray_x = map_x;
				*ray_y = py + (map_x - px) * tan(ray_angle);
			}
			else
			{
				*side = 1; // impacto horizontal (norte/sur)
				if (sin(ray_angle) > 0)
					map_y = (int)(*ray_y);
				else
					map_y = (int)(*ray_y) + 1;
				*ray_y = map_y;
				*ray_x = px + (map_y - py) / tan(ray_angle);
			}
			break ;
		}
		distance += STEP;
	}
	return (distance);
}

void	cast_rays(t_game *game)
{
	int				x;
	double			ray_angle;
	double			player_angle;
	double			ray_step;
	double			distance;
	int				wall_height;
	double			ray_x;
	double			ray_y;
	double			wall_hit;
	int				tex_x;
	int				side;
	t_render_info	r;

	player_angle = game->settings.player_angle;
	ray_step = FOV / WIN_WIDTH;
	ray_angle = player_angle - (FOV / 2);
	x = 0;
	while (x < WIN_WIDTH)
	{
		distance = cast_single_ray(game, ray_angle, &ray_x, &ray_y, &side);
		distance *= cos(ray_angle - player_angle); // Fisheye correction
		wall_height = (int)(WIN_HEIGHT / distance);
		if (wall_height > WIN_HEIGHT)
			wall_height = WIN_HEIGHT;
		if (side == 0)
			wall_hit = ray_y - floor(ray_y); // vertical
		else
			wall_hit = ray_x - floor(ray_x); // horizontal
		tex_x = (int)(wall_hit * game->textures->width);
		if (side == 0 && cos(ray_angle) < 0)
			tex_x = game->textures->width - tex_x - 1;
		if (side == 1 && sin(ray_angle) > 0)
			tex_x = game->textures->width - tex_x - 1;
		if (tex_x < 0)
			tex_x = 0;
		if (tex_x >= game->textures->width)
			tex_x = game->textures->width - 1;
		if (side == 0) //vertical
		{
			if (cos(ray_angle) > 0)
				r.texture_data = game->textures->we_data;
			else
				r.texture_data = game->textures->ea_data;
		}
		else //horizontal
		{
			if (sin(ray_angle) > 0)
				r.texture_data = game->textures->no_data;
			else
				r.texture_data = game->textures->so_data;
		}
		r.x = x;
		r.tex_x = tex_x;
		r.wall_height = wall_height;
		draw_textured_column(game, r);
		ray_angle += ray_step;
		x++;
	}
}
