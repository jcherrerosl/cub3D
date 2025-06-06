/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:09:20 by juanherr          #+#    #+#             */
/*   Updated: 2025/06/06 18:05:26 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (!game->started && keycode == KEY_SPACE)
	{
		game->started = 1;
		game->start_frame = 0;
		return (0);
	}
	if (keycode == KEY_W)
		game->key_state->w = 1;
	else if (keycode == KEY_A)
		game->key_state->a = 1;
	else if (keycode == KEY_S)
		game->key_state->s = 1;
	else if (keycode == KEY_D)
		game->key_state->d = 1;
	else if (keycode == KEY_LEFT)
		game->key_state->left = 1;
	else if (keycode == KEY_RIGHT)
		game->key_state->right = 1;
	else if (keycode == KEY_ESC)
		close_window(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->key_state->w = 0;
	else if (keycode == KEY_A)
		game->key_state->a = 0;
	else if (keycode == KEY_S)
		game->key_state->s = 0;
	else if (keycode == KEY_D)
		game->key_state->d = 0;
	else if (keycode == KEY_LEFT)
		game->key_state->left = 0;
	else if (keycode == KEY_RIGHT)
		game->key_state->right = 0;
	return (0);
}

int	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	ft_printf("Exiting game\n");
	mlx_destroy_window(game->img.mlx, game->img.win);
	exit(0);
}

void	draw_intro(t_game *game)
{
	if (!game->started)
	{
		mlx_put_image_to_window(game->img.mlx, game->img.win, game->intro_img,
			0, 0);
		game->start_frame++;
	}
	else
	{
		game->started = 1;
		game->start_frame = 0;
	}
}

int	render_frame(void *param)
{
	t_game	*g;
	double	now;

	g = (t_game *)param;
	now = now_ms();
	g->dt = (now - g->last_ms) / 1000.0;
	g->last_ms = now;
	if (!g->started)
		return (draw_intro(g), 0);
	handle_movement(g);
	ft_memset(g->img.addr, 0, WIN_WIDTH * WIN_HEIGHT * (g->img.bpp / 8));
	draw_floor_and_ceiling(g);
	cast_rays(g);
	draw_minimap(g);
	draw_gun(g, g->img.img);
	mlx_put_image_to_window(g->img.mlx, g->img.win, g->img.img, 0, 0);
	return (0);
}
