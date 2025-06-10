/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:27:55 by juanherr          #+#    #+#             */
/*   Updated: 2025/06/10 13:47:28 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_check_dir(t_ray *r, double *dir)
{
	if (dir[0] < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (r->pos_x - r->map_x) * r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - r->pos_x) * r->delta_x;
	}
	if (dir[1] < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (r->pos_y - r->map_y) * r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - r->pos_y) * r->delta_y;
	}
}

static void	init_ray_values(t_game *g, t_ray *r, double *dir)
{
	dir[0] = cos(g->ray_angle2);
	dir[1] = sin(g->ray_angle2);
	r->pos_x = g->settings.player_x + 0.5;
	r->pos_y = g->settings.player_y + 0.5;
	r->map_x = (int)r->pos_x;
	r->map_y = (int)r->pos_y;
	if (dir[0] == 0)
		r->delta_x = 1e30;
	else
		r->delta_x = fabs(1.0 / dir[0]);
	if (dir[1] == 0)
		r->delta_y = 1e30;
	else
		r->delta_y = fabs(1.0 / dir[1]);
	init_check_dir(r, dir);
}

static void	perform_dda(t_game *g, t_ray *r, int *side)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_x;
			r->map_x += r->step_x;
			*side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_y;
			r->map_y += r->step_y;
			*side = 1;
		}
		if (r->map_y < 0 || r->map_x < 0 || !g->settings.map[r->map_y]
			|| r->map_x >= (int)ft_strlen(g->settings.map[r->map_y])
			|| g->settings.map[r->map_y][r->map_x] == '1')
			hit = 1;
	}
}

double	cast_single_ray(t_game *g, double *ray_x, double *ray_y, int *side)
{
	t_ray	r;
	double	dir[2];
	double	perp_dist;

	init_ray_values(g, &r, dir);
	perform_dda(g, &r, side);
	if (*side == 0)
		perp_dist = (r.map_x - r.pos_x + (1 - r.step_x) / 2.0) / dir[0];
	else
		perp_dist = (r.map_y - r.pos_y + (1 - r.step_y) / 2.0) / dir[1];
	*ray_x = r.pos_x + perp_dist * dir[0];
	*ray_y = r.pos_y + perp_dist * dir[1];
	return (fabs(perp_dist));
}
