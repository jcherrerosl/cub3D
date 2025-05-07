/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:37:21 by juanherr          #+#    #+#             */
/*   Updated: 2025/05/07 17:20:01 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_settings	s;
	t_img		img;
	int			i;

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
	parse_file(argv[1], &s);
	i = 0;
	while (s.map && s.map[i])
		printf("%s", s.map[i++]);
	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	mlx_key_hook(img.win, handle_key, NULL);
	mlx_hook(img.win, 17, 0, handle_exit, NULL);
	mlx_loop(img.mlx);
	return (0);
}
