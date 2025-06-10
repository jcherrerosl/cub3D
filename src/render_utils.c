/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:11:26 by juanherr          #+#    #+#             */
/*   Updated: 2025/06/10 11:07:50 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_textured_column(t_game *game, t_render_info r)
{
	int		y;
	int		tex_y;
	double	tex_pos;
	int		draw_start;

	draw_start = (WIN_HEIGHT / 2) - (r.wall_height / 2);
	if (draw_start < 0)
	{
		tex_pos = (double)game->textures->height / r.wall_height * -draw_start;
		draw_start = 0;
	}
	else
		tex_pos = 0;
	y = draw_start;
	while (y < WIN_HEIGHT && y < draw_start + r.wall_height)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= game->textures->height)
			tex_y = game->textures->height - 1;
		draw_pixel(&game->img, r.x, y, *(unsigned int *)(r.texture_data + tex_y
				* game->textures->line_len + r.tex_x * (game->textures->bpp
					/ 8)));
		tex_pos += (double)game->textures->height / r.wall_height;
		y++;
	}
}

void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_tile(t_img *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_TILE)
	{
		j = 0;
		while (j < MINIMAP_TILE)
		{
			draw_pixel(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}
