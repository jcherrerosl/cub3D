/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:09:28 by juanherr          #+#    #+#             */
/*   Updated: 2025/05/21 00:16:58 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		ft_printerror("Invalid number of arguments\n");
	if (!check_extension(argv[1]))
		ft_printerror("Invalid file extension\n Expected [map_name].cub\n");
	init_settings(&game.settings);
	parse_file(argv[1], &game.settings);
	init_game(&game);
	game.started = 0;
	game.intro_img = mlx_xpm_file_to_image(
		game.img.mlx, "assets/intro.xpm", &game.intro_w, &game.intro_h);
	if (!game.intro_img)
		ft_printerror("Could not load intro image\n");
	game.gun = mlx_xpm_file_to_image(
		game.img.mlx, "assets/gun.xpm", &game.gun_w, &game.gun_h);
	if (!game.gun)
		ft_printerror("Could not load gun image\n");
	mlx_loop_hook(game.img.mlx, render_frame, &game);
	mlx_hook(game.img.win, 6, (1L << 6), mouse_handler, &game);
	mlx_hook(game.img.win, 2, (1L << 0), key_press, &game);
	mlx_hook(game.img.win, 3, (1L << 1), key_release, &game);
	mlx_hook(game.img.win, 17, 0, close_window, &game);
	mlx_loop(game.img.mlx);
	return (0);
}
