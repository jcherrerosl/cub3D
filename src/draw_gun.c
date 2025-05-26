/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:29:29 by juanherr          #+#    #+#             */
/*   Updated: 2025/05/26 15:33:43 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_offsets(t_game *game, t_gun *g)
{
	g->x_offset = (WIN_WIDTH - game->gun_width) / 2;
	g->y_offset = WIN_HEIGHT - game->gun_height;
}

static void	draw_gun_pixel(t_img *dst, int x, int y, int color)
{
	char	*dst_pixel;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst_pixel = dst->addr + (y * dst->line_len + x * (dst->bpp / 8));
	*(unsigned int *)dst_pixel = color;
}

void	draw_gun(t_game *game, void *frame_img)
{
	t_gun	g;

	g.gun_pixels = (int *)mlx_get_data_addr(game->gun_img, &g.bpp1,
			&g.line_len1, &g.endian1);
	g.frame_buffer = (int *)mlx_get_data_addr(frame_img, &g.bpp2, &g.line_len2,
			&g.endian2);
	game->img.addr = (char *)g.frame_buffer;
	game->img.bpp = g.bpp2;
	game->img.line_len = g.line_len2;
	game->img.endian = g.endian2;
	get_offsets(game, &g);
	g.y = 0;
	while (g.y < game->gun_height)
	{
		g.x = 0;
		while (g.x < game->gun_width)
		{
			g.color = g.gun_pixels[g.y * (g.line_len1 / 4) + g.x];
			if (g.color != 0xFF00FF)
				draw_gun_pixel(&game->img, g.x + g.x_offset, g.y + g.y_offset,
					g.color);
			g.x++;
		}
		g.y++;
	}
}
