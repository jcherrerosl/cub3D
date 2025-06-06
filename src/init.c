/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:34:00 by juanherr          #+#    #+#             */
/*   Updated: 2025/06/06 18:11:16 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_key_state	*init_key_state(t_game *game)
{
	t_key_state	*key_state;

	(void)game;
	key_state = malloc(sizeof(t_key_state));
	if (!key_state)
		ft_printerror("Could not allocate memory for key state");
	key_state->w = 0;
	key_state->a = 0;
	key_state->s = 0;
	key_state->d = 0;
	key_state->left = 0;
	key_state->right = 0;
	return (key_state);
}

static void	init_camera(t_camera *camera)
{
	camera->prev_x = 0;
	camera->prev_y = 0;
	camera->sensitivity = 0.0005;
	camera->vert_offset = 0.0;
}

void	init_settings(t_settings *s)
{
	ft_memset(s, 0, sizeof(t_settings));
	s->floor_rgb[0] = -1;
	s->ceiling_rgb[0] = -1;
}

void	init_game(t_game *game)
{
	game->img.mlx = mlx_init();
	if (!game->img.mlx)
		ft_printerror("Could not initialize mlx");
	game->img.win = mlx_new_window(game->img.mlx, WIN_WIDTH, WIN_HEIGHT,
			"Cub3D");
	if (!game->img.win)
		ft_printerror("Could not create window");
	game->img.img = mlx_new_image(game->img.mlx, WIN_WIDTH, WIN_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	game->started = 0;
	game->start_frame = 0;
	game->camera = malloc(sizeof(t_camera));
	if (!game->camera)
		ft_printerror("Could not allocate memory for camera");
	init_camera(game->camera);
	game->key_state = init_key_state(game);
	game->textures = init_textures(game);
	game->last_ms = now_ms();
	game->dt = 0.0;
	game->move_speed = MOVE_SPEED;
	game->rot_speed = ROT_SPEED;
	init_gun_sprite(game);
}
