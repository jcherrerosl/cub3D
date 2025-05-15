/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:11:26 by juanherr          #+#    #+#             */
/*   Updated: 2025/05/15 11:56:13 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_textured_column(t_game *game, t_render_info r)
{
	int		y;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		color;
	int		draw_start;
	int		draw_end;
	char	*texture;

	texture = r.texture_data;
	step = (double)game->textures->height / r.wall_height;
	draw_start = (WIN_HEIGHT / 2) - (r.wall_height / 2);
	draw_end = draw_start + r.wall_height;
	if (draw_start < 0)
	{
		tex_pos = step * -draw_start;
		draw_start = 0;
	}
	else
		tex_pos = 0;
	y = draw_start;
	while (y < WIN_HEIGHT && y < draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= game->textures->height)
			tex_y = game->textures->height - 1;
		color = *(unsigned int *)(texture + tex_y * game->textures->line_len
				+ r.tex_x * (game->textures->bpp / 8));
		draw_pixel(&game->img, r.x, y, color);
		tex_pos += step;
		y++;
	}
}
