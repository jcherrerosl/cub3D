/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:34:00 by juanherr          #+#    #+#             */
/*   Updated: 2025/05/09 03:25:26 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_settings(t_settings *s)
{
	ft_memset(s, 0, sizeof(t_settings));
	s->floor_rgb[0] = -1;
	s->ceiling_rgb[0] = -1;
}

void init_game(t_game *game)
{
	game->img.mlx = mlx_init();
	if (!game->img.mlx)
	{
		printf("Error: no se pudo inicializar mlx\n");
		exit(1);
	}
	game->img.win = mlx_new_window(game->img.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!game->img.win)
	{
		printf("Error: no se pudo crear la ventana\n");
		exit(1);
	}
	game->started = 0;
	game->start_frame = 0;
}