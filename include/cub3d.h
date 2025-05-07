/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:37:51 by juanherr          #+#    #+#             */
/*   Updated: 2025/05/07 17:22:49 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

typedef struct s_settings
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor_rgb[3];
	int		ceiling_rgb[3];
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	char	player_dir;
}			t_settings;

typedef struct s_img
{
	void	*mlx;
	void	*win;
}			t_img;

//init.c
void	init_settings(t_settings *settings);

//events.c
int		handle_key(int keycode, void *param);
int		handle_exit(void *param);

//parse_map.c
int		check_extension(const char *filename);

# define KEY_ESC 65307


#endif