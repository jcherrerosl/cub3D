/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:09:20 by juanherr          #+#    #+#             */
/*   Updated: 2025/05/21 20:28:56 by juanherr         ###   ########.fr       */
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

int	render_frame(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game->started)
	{
		mlx_clear_window(game->img.mlx, game->img.win);
		mlx_put_image_to_window(game->img.mlx, game->img.win, game->intro_img,
				(WIN_WIDTH - game->intro_w) / 2, (WIN_HEIGHT - game->intro_h)
				/ 2);
	}
	else
	{
		ft_memset(game->img.addr, 0, WIN_WIDTH * WIN_HEIGHT * (game->img.bpp
					/ 8));
		if (game->start_frame < 120)
		{
			mlx_clear_window(game->img.mlx, game->img.win);
			mlx_string_put(game->img.mlx, game->img.win, 580, 350, 0xAAAAAA,
					"Game starting...");
			game->start_frame++;
		}
		else
		{
			handle_movement(game);
			ft_memset(game->img.addr, 0, WIN_WIDTH * WIN_HEIGHT * (game->img.bpp
						/ 8));
			//	draw_map(game);								//orden por capas inverso (al final)
			draw_floor_and_ceiling(game); //fondo
			cast_rays(game);              //medio
			draw_minimap(game);           //encima
			// draw weapon y objetivo
			mlx_put_image_to_window(game->img.mlx, game->img.win, game->img.img,
					0, 0);
			mlx_put_image_to_window(game->img.mlx, game->img.win, game->img.img,
					0, 0);
			draw_gun(game, game->img.img);
			mlx_put_image_to_window(game->img.mlx, game->img.win, game->img.img,
					0, 0);
		}
	}
	return (0);
}
