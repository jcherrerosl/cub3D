/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:22:51 by juanherr          #+#    #+#             */
/*   Updated: 2025/05/26 15:18:31 by juanherr         ###   ########.fr       */
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

static inline int	is_vertical_hit(double x)
{
	return (fabs(x - floor(x + EPS)) < EPS);
}

/* -----------------------------------------------------------
 *  Devuelve:
 *      - distancia perpendicular hasta la pared
 *      - coordenada exacta del impacto  →  *ray_x / *ray_y
 *      - 0 si chocamos contra una línea vertical  (cara E/W)
 *      - 1 si chocamos contra una línea horizontal (cara N/S)
 * ----------------------------------------------------------- */
double	cast_single_ray(t_game *game, double ray_angle, double *ray_x,
		double *ray_y, int *side)
{
	double	dir_x;
	double	dir_y;
	double	pos_x;
	double	pos_y;
	int		map_x;
	int		map_y;
	double	delta_x;
	double	delta_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	double	perp_dist;

	/* 1. Dirección del rayo  */
	dir_x = cos(ray_angle);
	dir_y = sin(ray_angle);
	/* 2. Posición del jugador (centro del tile) */
	pos_x = game->settings.player_x + 0.5;
	pos_y = game->settings.player_y + 0.5;
	/* 3. Casilla actual */
	map_x = (int)pos_x;
	map_y = (int)pos_y;
	/* 4. Distancias entre grid-lines */
	if (dir_x == 0)
		delta_x = 1e30;
	else
		delta_x = fabs(1.0 / dir_x);

	if (dir_y == 0)
		delta_y = 1e30;
	else
		delta_y = fabs(1.0 / dir_y);
	/* 5. Distancia hasta **la PRÓXIMA** grid-line en cada eje */
	if (dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (pos_x - map_x) * delta_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - pos_x) * delta_x;
	}
	if (dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (pos_y - map_y) * delta_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - pos_y) * delta_y;
	}
	/* 6. DDA: avanzamos hasta entrar en un muro (‘1’) */
	hit = 0;
	while (!hit)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_x;
			map_x += step_x;
			*side = 0; /* impacto vertical */
		}
		else
		{
			side_dist_y += delta_y;
			map_y += step_y;
			*side = 1; /* impacto horizontal */
		}
		if (map_y < 0 || map_x < 0 ||
			!game->settings.map[map_y] ||
			map_x >= (int)ft_strlen(game->settings.map[map_y]) ||
			game->settings.map[map_y][map_x] == '1')
			hit = 1;
	}
	/* 7. Distancia perpendicular y coordenada de impacto */
	if (*side == 0) /* vertical */
	{
		perp_dist = (map_x - pos_x + (1 - step_x) / 2.0) / dir_x;
	}
	else /* horizontal */
	{
		perp_dist = (map_y - pos_y + (1 - step_y) / 2.0) / dir_y;
	}
	*ray_x = pos_x + perp_dist * dir_x;
	*ray_y = pos_y + perp_dist * dir_y;
	return (fabs(perp_dist));
}

/* ------------------------------------------------------------------------- */
/*  l   Ray–casting principal: lanza WIN_WIDTH rayos e imprime cada columna  */
/* ------------------------------------------------------------------------- */
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
	int				side;
//	double			wall_x;
	int				tex_x;
	t_render_info	r;

//	const int tex_w = game->textures->width; /* ← ancho de TODAS las texturas */
	player_angle = game->settings.player_angle;
	ray_step = FOV / WIN_WIDTH;
	ray_angle = player_angle - (FOV / 2.0);
	x = 0;
	while (x < WIN_WIDTH)
	{
		/* ------------- DDA: lanzamos UN rayo ------------- */
		distance = cast_single_ray(game, ray_angle, &ray_x, &ray_y, &side);
		distance = cast_single_ray(game, ray_angle, &ray_x, &ray_y, &side);
		/* Altura en pantalla de la pared encontrada */
		wall_height = (int)(WIN_HEIGHT / distance);
		// if (wall_height > WIN_HEIGHT)
		// 	wall_height = WIN_HEIGHT;
		/* fracción de pared recorrida */
		double wall_x;
		if (side == 0)
			wall_x = ray_y - floor(ray_y);
		else
			wall_x = ray_x - floor(ray_x);
		tex_x = (int)(wall_x * game->textures->width);
		/* invertir la franja si miramos “desde detrás” */
		if ((side == 0 && cos(ray_angle) < 0) ||
			(side == 1 && sin(ray_angle) > 0))
			tex_x = game->textures->width - tex_x - 1;
		/* elegir textura coherente (ver tabla anterior) */
		if (side == 0) /* vertical */
		{
			if (cos(ray_angle) > 0)
				r.texture_data = game->textures->we_data;
			else
				r.texture_data = game->textures->ea_data;
		}
		else /* horizontal */
		{
			if (sin(ray_angle) > 0)
				r.texture_data = game->textures->no_data;
			else
				r.texture_data = game->textures->so_data;
		}
		/* ------------- Lanzamos la columna a la rutina de pintado ------------- */
		r.x = x;
		r.tex_x = tex_x;
		r.wall_height = wall_height;
		draw_textured_column(game, r);
		ray_angle += ray_step;
		++x;
	}
}
