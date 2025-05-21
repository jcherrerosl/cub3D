/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiki <aloiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:57:25 by aloiki            #+#    #+#             */
/*   Updated: 2025/05/21 21:22:40 by aloiki           ###   ########.fr       */
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
	map_y = (int)floor(game->settings.player_y);
	if (game->settings.map[map_y] &&
		map_x < (int)ft_strlen(game->settings.map[map_y]) &&
		game->settings.map[map_y][map_x] != '1')
		game->settings.player_x = new_x;
	if (new_y > game->settings.player_y)
		buffer_y = COLLISION_BUFFER;
	else
		buffer_y = -COLLISION_BUFFER;
	map_x = (int)floor(game->settings.player_x);
	map_y = (int)floor(new_y + buffer_y + 0.5);
	if (game->settings.map[map_y] &&
		map_x < (int)ft_strlen(game->settings.map[map_y]) &&
		game->settings.map[map_y][map_x] != '1')
		game->settings.player_y = new_y;
}

void	handle_movement(t_game *game)
{
	double	angle;
	double	new_x;
	double	new_y;

	angle = game->settings.player_angle;
	new_x = game->settings.player_x;
	new_y = game->settings.player_y;
	if (game->key_state->w)
	{
		new_x += cos(angle) * MOVE_SPEED;
		new_y += sin(angle) * MOVE_SPEED;
	}
	if (game->key_state->s)
	{
		new_x -= cos(angle) * MOVE_SPEED;
		new_y -= sin(angle) * MOVE_SPEED;
	}
	if (game->key_state->d)
	{
		new_x += cos(angle + M_PI / 2) * MOVE_SPEED;
		new_y += sin(angle + M_PI / 2) * MOVE_SPEED;
	}
	if (game->key_state->a)
	{
		new_x += cos(angle - M_PI / 2) * MOVE_SPEED;
		new_y += sin(angle - M_PI / 2) * MOVE_SPEED;
	}
	collision_check(game, new_x, new_y);
	if (game->key_state->left)
		game->settings.player_angle -= 0.05;
	if (game->key_state->right)
		game->settings.player_angle += 0.05;
	if (game->settings.player_angle < 0)
		game->settings.player_angle += 2 * M_PI;
	if (game->settings.player_angle >= 2 * M_PI)
		game->settings.player_angle -= 2 * M_PI;
}
