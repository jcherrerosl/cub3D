/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiki <aloiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:34:44 by aloiki            #+#    #+#             */
/*   Updated: 2025/05/14 01:14:31 by aloiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_up_down(t_game *game, int pos_y)
{
	double	new_offset;

	new_offset = game->camera->vert_offset + pos_y * game->camera->sensitivity * 500;
	if (new_offset > MAX_VERTICAL_OFFSET)
		new_offset = MAX_VERTICAL_OFFSET;
	if (new_offset < -MAX_VERTICAL_OFFSET)
		new_offset = -MAX_VERTICAL_OFFSET;
	game->camera->vert_offset = new_offset;
	
}

void	rotate_left_right(t_game *game, int pos_x)
{
	double	angle;

	angle = pos_x * game->camera->sensitivity;
	game->settings.player_angle += angle;
	if (game->settings.player_angle < 0)
       		game->settings.player_angle += 2 * M_PI;
    	if (game->settings.player_angle >= 2 * M_PI)
        	game->settings.player_angle -= 2 * M_PI;
}

int	mouse_handler(int x, int y, t_game *game)
{
	static int	prev_x = WIN_WIDTH / 2;
	static int	prev_y = WIN_HEIGHT / 2;
	int		pos_x = WIN_WIDTH / 2;
	int		pos_y = WIN_HEIGHT / 2;
	int		center_x = WIN_WIDTH / 2;

	if (!game->started)
		return (0);
	if (x == center_x && y == WIN_HEIGHT / 2)
		return (0);
	pos_x = x - prev_x;
	pos_y = y - prev_y;
	if (pos_x != 0)
		rotate_left_right(game, pos_x);
	if (pos_y != 0)
		rotate_up_down(game, pos_y);
	prev_x = x;
	prev_y = y;
	mlx_mouse_move(game->img.mlx, game->img.win, 
		center_x, WIN_HEIGHT / 2);
	return (0);
}
