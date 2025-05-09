#include "cub3d.h"

void	draw_tile(t_img *img, int x, int y, int color)
{
	int	i = 0;
	int	j;

	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_pixel_put(img->mlx, img->win, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (game->settings.map && game->settings.map[y])
	{
		x = 0;
		while (game->settings.map[y][x])
		{
			if (game->settings.map[y][x] == '1')
				color = COLOR_WALL;
			else
				color = COLOR_FLOOR;
			draw_tile(&game->img, x * TILE_SIZE, y * TILE_SIZE, color);
			x++;
		}
		y++;
	}
	draw_tile(&game->img,
		game->settings.player_x * TILE_SIZE + TILE_SIZE / 4,
		game->settings.player_y * TILE_SIZE + TILE_SIZE / 4,
		COLOR_PLAYER);
}
