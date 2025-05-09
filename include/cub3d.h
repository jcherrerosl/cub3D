/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:37:51 by juanherr          #+#    #+#             */
/*   Updated: 2025/05/09 12:50:53 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

# define TILE_SIZE 20
# define COLOR_WALL 0xAAAAAA
# define COLOR_FLOOR 0x111111
# define COLOR_CEILING 0x222222
# define COLOR_PLAYER 0xFF0000

# define KEY_ESC 65307
# define KEY_ENTER 65293
# define KEY_SPACE 32

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

typedef struct s_settings
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			floor_rgb[3];
	int			ceiling_rgb[3];
	char		**map;
	int			map_width;
	int			map_height;
	int			player_x;
	int			player_y;
	char		player_dir;
}				t_settings;

typedef struct s_img
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef struct s_game
{
	t_settings	settings;
	t_img		img;
	void		*intro_img;
	int			intro_w;
	int			intro_h;
	int			started;
	int			start_frame;

}				t_game;

//init.c
void			init_settings(t_settings *settings);
void			init_game(t_game *game);

//events.c
int				key_handler(int key, void *param);
int				close_window(void *param);
int				render_frame(void *param);

//parse_map.c
int				check_extension(const char *filename);
int				is_map_line(char *line);
void			store_player(t_settings *s, int x, int y, char dir);
void			parse_file(const char *filename, t_settings *s);

//render.c
void			draw_pixel(t_img *img, int x, int y, int color);
void			draw_tile(t_img *img, int x, int y, int color);
void			draw_map(t_game *game);

#endif