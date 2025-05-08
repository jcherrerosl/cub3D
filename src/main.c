/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:37:21 by juanherr          #+#    #+#             */
/*   Updated: 2025/05/08 14:35:15 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_settings	s;
	t_img		img;

	if (argc != 2)
	{
		printf("Error: Incorrect number of arguments.\n");
		return (1);
	}
	if (!check_extension(argv[1]))
	{
		printf("Error: Expected [map_name].cub\n");
		return (1);
	}
	init_settings(&s);
	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	mlx_key_hook(img.win, key_handler, &img);
	mlx_hook(img.win, 17, 0, close_window, &img);
	mlx_loop(img.mlx);
	return (0);
}
