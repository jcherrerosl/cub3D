/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:34:44 by aloiki            #+#    #+#             */
/*   Updated: 2025/06/10 12:15:36 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_up_down(t_game *game, int pos_y)
{
	double	new_offset;

	new_offset = game->camera->vert_offset + pos_y * game->camera->sensitivity
		* 500;
	if (new_offset > MAX_VERTICAL_OFFSET)
		new_offset = MAX_VERTICAL_OFFSET;
	if (new_offset < -MAX_VERTICAL_OFFSET)
		new_offset = -MAX_VERTICAL_OFFSET;
	game->camera->vert_offset = new_offset;
}

void	rotate_left_right(t_game *game, int pos_x)
{
	double	angle;

	angle = pos_x * game->camera->sensitivity * 5;
	game->settings.player_angle += angle;
	if (game->settings.player_angle < 0)
		game->settings.player_angle += 2 * M_PI;
	if (game->settings.player_angle >= 2 * M_PI)
		game->settings.player_angle -= 2 * M_PI;
}

void	handle_mouse_edges(t_game *game, int x)
{
	if (x <= 10 || x >= WIN_WIDTH - 10)
	{
		mlx_mouse_move(game->img.mlx, game->img.win, WIN_WIDTH / 2, WIN_HEIGHT
			/ 2);
		game->mouse.ignore = 1;
	}
}

void	process_mouse_motion(t_game *game, int x, int y)
{
	int	pos_x;
	int	pos_y;

	pos_x = x - game->mouse.prev_x;
	pos_y = y - game->mouse.prev_y;
	if (pos_x != 0)
		rotate_left_right(game, pos_x);
	if (pos_y != 0)
		rotate_up_down(game, pos_y);
	game->mouse.prev_x = x;
	game->mouse.prev_y = y;
}

int	mouse_handler(int x, int y, t_game *game)
{
	if (!game->started)
		return (0);
	if (x == WIN_WIDTH / 2 && y == WIN_HEIGHT / 2)
		return (0);
	if (game->mouse.ignore == 1)
	{
		game->mouse.ignore = 0;
		game->mouse.prev_x = x;
		game->mouse.prev_y = y;
		return (0);
	}
	process_mouse_motion(game, x, y);
	handle_mouse_edges(game, x);
	return (0);
}
