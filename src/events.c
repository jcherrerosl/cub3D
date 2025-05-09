#include "cub3d.h"

int	key_handler(int keycode, void *param)
{
	t_game	*game = (t_game *)param;
	int		px = game->settings.player_x;
	int		py = game->settings.player_y;

	if (!game->started && keycode == 32)
	{
		game->started = 1;
		game->start_frame = 0;
	}
	else if (game->started)
	{
		if (keycode == KEY_W && py > 0
			&& game->settings.map[py - 1]
			&& px < (int)ft_strlen(game->settings.map[py - 1])
			&& game->settings.map[py - 1][px] != '1')
			game->settings.player_y--;
		else if (keycode == KEY_S
			&& game->settings.map[py + 1]
			&& px < (int)ft_strlen(game->settings.map[py + 1])
			&& game->settings.map[py + 1][px] != '1')
			game->settings.player_y++;
		else if (keycode == KEY_A && px > 0
			&& game->settings.map[py][px - 1] != '1')
			game->settings.player_x--;
		else if (keycode == KEY_D
			&& px + 1 < (int)ft_strlen(game->settings.map[py])
			&& game->settings.map[py][px + 1] != '1')
			game->settings.player_x++;
		else if (keycode == KEY_ESC)
			close_window(param);
	}
	return (0);
}



int	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	ft_printf("Exiting game\n");
	mlx_destroy_window(game->img.mlx, game->img.win);
	exit(0);
}

int	render_frame(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_clear_window(game->img.mlx, game->img.win);
	if (!game->started)
	{
		mlx_put_image_to_window(
			game->img.mlx,
			game->img.win,
			game->intro_img,
			(WIN_WIDTH - game->intro_w) / 2,
			(WIN_HEIGHT - game->intro_h) / 2);
	}
	else
	{
		if (game->start_frame < 120)
		{
			mlx_string_put(game->img.mlx, game->img.win, 580, 350, 0xAAAAAA,
					"Game starting...");
			game->start_frame++;
		}
		else
			draw_map(game);
	}
	return (0);
}
