/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiki <aloiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:09:20 by juanherr          #+#    #+#             */
/*   Updated: 2025/05/14 16:27:51 by aloiki           ###   ########.fr       */
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

// int	key_handler(int keycode, void *param)
// {
// 	t_game	*game;
// 	// double	new_x;
// 	// double	new_y;
// 	// double	angle;
// 	// int		map_x;
// 	// int		map_y;

// 	game = (t_game *)param;
// 	// angle = game->settings.player_angle;
// 	if (!game->started && keycode == KEY_SPACE)
// 	{
// 		game->started = 1;
// 		game->start_frame = 0;
// 	}
// 	// else if (game->started)
// 	// {
// 	// 	new_x = game->settings.player_x;
// 	// 	new_y = game->settings.player_y;
// 		// if (keycode == KEY_W)  
// 		// {
// 		// 	new_x += cos(angle) * MOVE_SPEED;
// 		// 	new_y += sin(angle) * MOVE_SPEED;
// 		// }
// 		// else if (keycode == KEY_S) //chequear bien ???? no estoy seguro 
// 		// {
// 		// 	new_x -= cos(angle) * MOVE_SPEED;
// 		// 	new_y -= sin(angle) * MOVE_SPEED;
// 		// }
// 		// else if (keycode == KEY_D)
// 		// {
// 		// 	new_x += cos(angle + M_PI / 2) * MOVE_SPEED;
// 		// 	new_y += sin(angle + M_PI / 2) * MOVE_SPEED;
// 		// }
// 		// else if (keycode == KEY_A)
// 		// {
// 		// 	new_x += cos(angle - M_PI / 2) * MOVE_SPEED;
// 		// 	new_y += sin(angle - M_PI / 2) * MOVE_SPEED;
// 		// }
// 		// else if (keycode == KEY_LEFT)
// 		// 	game->settings.player_angle -= 0.05;
// 		// else if (keycode == KEY_RIGHT)
// 		// 	game->settings.player_angle += 0.05;
// 		else if (keycode == KEY_ESC)
// 			close_window(param);
// 		// else
// 		// 	return (0);
// 		// if (game->settings.player_angle < 0)
// 		// 	game->settings.player_angle += 2 * M_PI;
// 		// if (game->settings.player_angle >= 2 * M_PI)
// 		// 	game->settings.player_angle -= 2 * M_PI;
// 		// if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A
// 		// 	|| keycode == KEY_D)
// 		// {
// 		// 	map_x = (int)new_x;
// 		// 	map_y = (int)game->settings.player_y;
// 		// 	if (game->settings.map[map_y] &&
// 		// 		map_x < (int)ft_strlen(game->settings.map[map_y]) &&
// 		// 		game->settings.map[map_y][map_x] != '1')
// 		// 		game->settings.player_x = new_x;
// 		// 	map_x = (int)game->settings.player_x;
// 		// 	map_y = (int)new_y;
// 		// 	if (game->settings.map[map_y] &&
// 		// 		map_x < (int)ft_strlen(game->settings.map[map_y]) &&
// 		// 		game->settings.map[map_y][map_x] != '1')
// 		// 		game->settings.player_y = new_y;
// 		// }
// 	// }
// 	return (0);
// }

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
			ft_memset(game->img.addr, 0, WIN_WIDTH * WIN_HEIGHT * (game->img.bpp / 8));
		//	draw_map(game);								//orden por capas inverso (al final)
			cast_rays(game);														//medio
			draw_minimap(game);														//encima
			mlx_put_image_to_window(game->img.mlx, game->img.win, game->img.img, 0, 0);
		}
	}
	return (0);
}
