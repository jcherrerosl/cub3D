/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:37:51 by juanherr          #+#    #+#             */
/*   Updated: 2025/06/16 01:18:24 by juanherr         ###   ########.fr       */
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
# include <sys/time.h>

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define MINIMAP_RATIO 0.5
# define MINIMAP_TILE 10

# define MAX_VERTICAL_OFFSET 200
# define COLLISION_BUFFER 0.1

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# ifndef M_PI_2
#  define M_PI_2 1.57079632679489661923
# endif

# define MOVE_SPEED 3
# define ROT_SPEED 1

# define FOV 1.0471975512
# define NUM_RAYS 3840

# define TILE_SIZE 20
# define COLOR_WALL 0xAAAAAA
# define COLOR_FLOOR 0x111111
# define COLOR_CEILING 0x222222
# define COLOR_PLAYER 0xFF0000
# define COLOR_CONE 0x00FFFF

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
	int				no_num;
	char			*so;
	int				so_num;
	char			*we;
	int				we_num;
	char			*ea;
	int				ea_num;
	int				f_num;
	int				c_num;
	int				enclosed;
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

typedef struct s_gun
{
	int				*gun_pixels;
	int				*frame_buffer;
	int				x_offset;
	int				y_offset;
	int				bpp1;
	int				line_len1;
	int				endian1;
	int				bpp2;
	int				line_len2;
	int				endian2;
	int				color;
	int				x;
	int				y;
}					t_gun;

typedef struct s_mouse
{
	int				prev_x;
	int				prev_y;
	int				ignore;
}					t_mouse;

typedef struct s_ray
{
	double			pos_x;
	double			pos_y;
	int				map_x;
	int				map_y;
	double			delta_x;
	double			delta_y;
	double			side_dist_x;
	double			side_dist_y;
	int				step_x;
	int				step_y;
}					t_ray;

typedef struct s_ray_hit
{
	double			x;
	double			y;
	int				side;
}					t_ray_hit;

typedef struct s_game
{
	t_settings		settings;
	t_img			img;
	t_camera		*camera;
	t_key_state		*key_state;
	t_textures		*textures;
	t_render_info	render_info[WIN_WIDTH];
	t_gun			*gun;
	t_mouse			mouse;
	t_ray_hit		hit;
	void			*intro_img;
	int				intro_w;
	int				intro_h;
	void			*gun_img;
	int				gun_width;
	int				gun_height;
	int				started;
	int				start_frame;
	double			last_ms;
	double			dt;
	double			move_speed;
	double			rot_speed;
	int				center_x;
	int				center_y;
	double			radius;
	double			angle;
	double			fov;
	int				color;
	double			start_angle;
	double			ray_angle;
	double			ray_angle2;
	double			ray_x;
	double			ray_y;
	int				side;
}					t_game;

// init.c
void				init_settings(t_settings *settings);
void				init_game(t_game *game);
void				init_gun_sprite(t_game *game);

// init_textures.c
t_textures			*init_textures(t_game *game);

// events.c
int					close_window(void *param);
int					render_frame(void *param);
int					key_press(int keycode, t_game *game);
int					key_release(int keycode, t_game *game);
double				now_ms(void);

// parse_map.c
int					check_extension(const char *filename);
void				check_map_enclosed(t_settings *s);
void				check_content(int *num, char **str_to_save, char *line,
						char *error_msg);
void				check_f_color(char *line, t_settings *s);
void				check_c_color(char *line, t_settings *s);
int					count_map_lines(const char *filename);
int					in_map(t_settings *s);
int					is_map_line(char *line);
void				store_player(t_settings *s, int x, int y, char dir);
void				parse_file(const char *filename, t_settings *s);
void				parse_map_chars(t_settings *s);
void				find_player(t_settings *s);
void				fill_map(t_settings *s, char ***map, int fd);

// render.c
void				draw_pixel(t_img *img, int x, int y, int color);
void				draw_tile(t_img *img, int x, int y, int color);
void				draw_map(t_game *game);
void				draw_minimap(t_game *game);
void				draw_gun(t_game *game, void *frame_img);
void				draw_column(t_game *game, int x, int wall_height,
						int color);
void				draw_textured_column(t_game *game, t_render_info r);

// raycasting.c
void				draw_column(t_game *game, int x, int wall_height,
						int color);
void				cast_rays(t_game *game);
double				cast_single_ray(t_game *g, double *ray_x, double *ray_y,
						int *side);

// mouse_input.c
int					mouse_handler(int x, int y, t_game *game);
void				rotate_left_right(t_game *game, int pos_x);

// movement.c
void				handle_movement(t_game *game);
void				w_pressed(double *player_x, double *player_y, double angle,
						double step);
void				s_pressed(double *player_x, double *player_y, double angle,
						double step);
void				d_pressed(double *player_x, double *player_y, double angle,
						double step);
void				a_pressed(double *player_x, double *player_y, double angle,
						double step);
void				init_vars1(double *rot, double *angle, double *nx,
						t_game *g);
void				init_vars2(double *ny, double *step, t_game *g);

// general_utils.c
int					ft_isdigit_str(char *s);
void				free_matrix(char **matrix);

// parse_textures.c
int					parse_color(char *line, int *color);
void				draw_floor_and_ceiling(t_game *game);

#endif