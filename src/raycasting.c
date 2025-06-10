/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:22:51 by juanherr          #+#    #+#             */
/*   Updated: 2025/06/10 14:01:01 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_rays(t_game *game)
{
	int				x;
	double			player_angle;
	double			ray_step;
	double			distance;
	int				wall_height;
	double			ray_x;
	double			ray_y;
	int				side;
	int				tex_x;
	t_render_info	r;
	double			wall_x;

	player_angle = game->settings.player_angle;
	ray_step = FOV / WIN_WIDTH;
	game->ray_angle2 = player_angle - (FOV / 2.0);
	x = 0;
	while (x < WIN_WIDTH)
	{
		/* ------------- DDA: lanzamos UN rayo ------------- */
		distance = cast_single_ray(game, &ray_x, &ray_y, &side);
		distance *= cos(game->ray_angle2 - player_angle); /* corrección de distancia */
		/* Altura en pantalla de la pared encontrada */
		wall_height = (int)(WIN_HEIGHT / distance);
		/* fracción de pared recorrida */
		if (side == 0) /* vertical */
			wall_x = ray_y - floor(ray_y);
		else /* horizontal */
			wall_x = ray_x - floor(ray_x);
		tex_x = (int)(wall_x * game->textures->width);
		/* invertir la franja si miramos “desde detrás” */
		if ((side == 0 && cos(game->ray_angle2) < 0) ||
			(side == 1 && sin(game->ray_angle2) > 0))
			tex_x = game->textures->width - tex_x - 1;
		/* elegir textura coherente (ver tabla anterior) */
		if (side == 0) /* vertical */
		{
			if (cos(game->ray_angle2) > 0)
				r.texture_data = game->textures->we_data;
			else
				r.texture_data = game->textures->ea_data;
		}
		else /* horizontal */
		{
			if (sin(game->ray_angle2) > 0)
				r.texture_data = game->textures->no_data;
			else
				r.texture_data = game->textures->so_data;
		}
		/* ------------- Lanzamos la columna a la rutina de pintado ------------- */
		r.x = x;
		r.tex_x = tex_x;
		r.wall_height = wall_height;
		draw_textured_column(game, r);
		game->ray_angle2 += ray_step;
		++x;
	}
}
