/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:22:51 by juanherr          #+#    #+#             */
/*   Updated: 2025/06/10 14:07:59 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_ray_angle(t_game *game, double player_angle)
{
	game->ray_angle2 = player_angle - (FOV / 2.0);
}

static void	calculate_wall_props(t_game *game, t_render_info *r, double ray_x,
		double ray_y)
{
	double	wall_x;
	int		tex_x;

	if (game->side == 0)
		wall_x = ray_y - floor(ray_y);
	else
		wall_x = ray_x - floor(ray_x);
	tex_x = (int)(wall_x * game->textures->width);
	if ((game->side == 0 && cos(game->ray_angle2) < 0) || (game->side == 1
			&& sin(game->ray_angle2) > 0))
		tex_x = game->textures->width - tex_x - 1;
	r->tex_x = tex_x;
}

static void	select_texture(t_game *game, t_render_info *r)
{
	if (game->side == 0)
	{
		if (cos(game->ray_angle2) > 0)
			r->texture_data = game->textures->we_data;
		else
			r->texture_data = game->textures->ea_data;
	}
	else
	{
		if (sin(game->ray_angle2) > 0)
			r->texture_data = game->textures->no_data;
		else
			r->texture_data = game->textures->so_data;
	}
}

static void	cast_single_ray_column(t_game *game, int x, double player_angle)
{
	t_render_info	r;
	double			ray_x;
	double			ray_y;
	double			distance;

	distance = cast_single_ray(game, &ray_x, &ray_y, &game->side);
	distance *= cos(game->ray_angle2 - player_angle);
	r.wall_height = (int)(WIN_HEIGHT / distance);
	calculate_wall_props(game, &r, ray_x, ray_y);
	select_texture(game, &r);
	r.x = x;
	draw_textured_column(game, r);
}

void	cast_rays(t_game *game)
{
	int		x;
	double	player_angle;
	double	ray_step;

	player_angle = game->settings.player_angle;
	ray_step = FOV / WIN_WIDTH;
	set_ray_angle(game, player_angle);
	x = 0;
	while (x < WIN_WIDTH)
	{
		cast_single_ray_column(game, x, player_angle);
		game->ray_angle2 += ray_step;
		++x;
	}
}
