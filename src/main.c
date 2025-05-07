/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:37:21 by juanherr          #+#    #+#             */
/*   Updated: 2025/05/07 13:00:08 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_key(int keycode, void *param)
{
	(void)param;
	if (keycode == 65307) // ESC key
		exit(0);
	return (0);
}

int	handle_exit(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int	main(void)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	if (!mlx)
		return (1);
	win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	mlx_key_hook(win, handle_key, NULL);
	mlx_hook(win, 17, 0, handle_exit, NULL);
	mlx_loop(mlx);
	return (0);
}
