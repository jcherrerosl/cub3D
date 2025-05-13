/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiki <aloiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:34:00 by juanherr          #+#    #+#             */
/*   Updated: 2025/05/14 00:33:01 by aloiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	{
		ft_printerror("Could not initialize mlx");
	}
	game->img.win = mlx_new_window(game->img.mlx, WIN_WIDTH, WIN_HEIGHT,
			"Cub3D");
	if (!game->img.win)
	{
		ft_printerror("Could not create window");
	}
	game->img.img = mlx_new_image(game->img.mlx, WIN_WIDTH, WIN_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img,
										&game->img.bpp,
										&game->img.line_len,
										&game->img.endian);

	game->started = 0;
	game->start_frame = 0;
	game->camera = malloc(sizeof(t_camera));
	if (!game->camera)
		ft_printerror("Could not allocate memory for camera");
	init_camera(game->camera);
}
