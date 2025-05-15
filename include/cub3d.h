/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:37:51 by juanherr          #+#    #+#             */
/*   Updated: 2025/05/15 12:01:52 by juanherr         ###   ########.fr       */
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

# define MINIMAP_RATIO 0.2
# define MINIMAP_TILE TILE_SIZE *MINIMAP_RATIO

# define MAX_VERTICAL_OFFSET 200

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define STEP 0.005
# define MOVE_SPEED 0.1

# define FOV (M_PI / 3)
# define NUM_RAYS WIN_WIDTH

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

# define KEY_LEFT 65361
# define KEY_RIGHT 65363

typedef struct s_settings
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				floor_rgb[3];
	int				ceiling_rgb[3];
	char			**map;
	int				map_width;
	int				map_height;
	double			player_x;
	double			player_y;
	char			player_dir;
	double			player_angle;
}					t_settings;

typedef struct s_img
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_img;

typedef struct s_camera
{
	int				prev_x;
	int				prev_y;
	double			sensitivity;
	double			vert_offset;
}					t_camera;

typedef struct s_key_state
{
	int				w;
	int				a;
	int				s;
	int				d;
	int				left;
	int				right;
}					t_key_state;

typedef struct s_textures
{
	void			*no;
	void			*so;
	void			*we;
	void			*ea;
	char			*no_data;
	char			*so_data;
	char			*we_data;
	char			*ea_data;
	int				width;
	int				height;
	int				bpp;
	int				line_len;
	int				endian;
}					t_textures;

typedef struct s_render_info
{
	int				x;
	int				tex_x;
	int				wall_height;
	char			*texture_data;
}					t_render_info;

typedef struct s_game
{
	t_settings		settings;
	t_img			img;
	t_camera		*camera;
	t_key_state		*key_state;
	t_textures		*textures;
	t_render_info	render_info[WIN_WIDTH];
	void			*intro_img;
	int				intro_w;
	int				intro_h;
	int				started;
	int				start_frame;
}					t_game;

//init.c
void				init_settings(t_settings *settings);
void				init_game(t_game *game);

//events.c
int					key_handler(int key, void *param);
int					close_window(void *param);
int					render_frame(void *param);
int					key_press(int keycode, t_game *game);
int					key_release(int keycode, t_game *game);

//parse_map.c
int					check_extension(const char *filename);
int					is_map_line(char *line);
void				store_player(t_settings *s, int x, int y, char dir);
void				parse_file(const char *filename, t_settings *s);

//render.c
void				draw_pixel(t_img *img, int x, int y, int color);
void				draw_tile(t_img *img, int x, int y, int color);
void				draw_map(t_game *game);
void				draw_minimap(t_game *game);

// raycasting.c
void				draw_column(t_game *game, int x, int wall_height,
						int color);
void				cast_rays(t_game *game);
double				cast_single_ray(t_game *game, double ray_angle,
						double *ray_x, double *ray_y, int *side);
void				draw_textured_column(t_game *game, t_render_info r);;

// mouse_input.c
int					mouse_handler(int x, int y, t_game *game);
void				rotate_left_right(t_game *game, int pos_x);

// movement.c
void				handle_movement(t_game *game);

// general_utils.c
int					ft_isdigit_str(char *s);
void				free_matrix(char **matrix);

// parse_textures.c
int					parse_color(char *line, int *color);
void				draw_floor_and_ceiling(t_game *game);

#endif