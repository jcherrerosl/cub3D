/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:57:25 by aloiki            #+#    #+#             */
/*   Updated: 2025/05/28 13:46:49 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	collision_check(t_game *game, double new_x, double new_y)
{
	int		map_x;
	int		map_y;
	double	buffer_x;
	double	buffer_y;

	if (new_x > game->settings.player_x)
		buffer_x = COLLISION_BUFFER;
	else
		buffer_x = -COLLISION_BUFFER;
	map_x = (int)floor(new_x + buffer_x + 0.5);
	map_y = (int)floor(game->settings.player_y + 0.5);
	if (game->settings.map[map_y] &&
		map_x < (int)floor(ft_strlen(game->settings.map[map_y])) &&
		game->settings.map[map_y][map_x] != '1')
		game->settings.player_x = new_x;
	if (new_y > game->settings.player_y)
		buffer_y = COLLISION_BUFFER;
	else
		buffer_y = -COLLISION_BUFFER;
	map_x = (int)floor(game->settings.player_x + 0.5);
	map_y = (int)floor(new_y + buffer_y + 0.5);
	if (game->settings.map[map_y] &&
		map_x < (int)floor(ft_strlen(game->settings.map[map_y])) &&
		game->settings.map[map_y][map_x] != '1')
		game->settings.player_y = new_y;
}

void	handle_movement(t_game *g)
{
	double	angle;
	double	nx;
	double	ny;

	double step = g->move_speed * g->dt; /* avance lateral/frontal        */
	double rot = g->rot_speed * g->dt;   /* giro izquierda/derecha        */
	angle = g->settings.player_angle;
	nx = g->settings.player_x;
	ny = g->settings.player_y;
	if (g->key_state->w)
	{
		nx += cos(angle) * step;
		ny += sin(angle) * step;
	}
	if (g->key_state->s)
	{
		nx -= cos(angle) * step;
		ny -= sin(angle) * step;
	}
	if (g->key_state->d)
	{
		nx += cos(angle + M_PI_2) * step;
		ny += sin(angle + M_PI_2) * step;
	}
	if (g->key_state->a)
	{
		nx += cos(angle - M_PI_2) * step;
		ny += sin(angle - M_PI_2) * step;
	}
	collision_check(g, nx, ny);
	if (g->key_state->left)
		g->settings.player_angle -= rot;
	if (g->key_state->right)
		g->settings.player_angle += rot;
	if (g->settings.player_angle < 0)
		g->settings.player_angle += 2 * M_PI;
	if (g->settings.player_angle >= 2 * M_PI)
		g->settings.player_angle -= 2 * M_PI;
}
