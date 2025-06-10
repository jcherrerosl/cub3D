/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:33:09 by juanherr          #+#    #+#             */
/*   Updated: 2025/06/10 12:26:17 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_color(char *str, int *rgb)
{
	char	**parts;
	char	*trim;
	int		i;

	parts = ft_split(str, ',');
	if (!parts)
		return (0);
	if (!parts[0] || !parts[1] || !parts[2] || parts[3])
		return (free_matrix(parts), 0);
	i = 0;
	while (i < 3)
	{
		trim = ft_strtrim(parts[i], " \t\n\r");
		if (!trim || !*trim)
			return (free(trim), free_matrix(parts), 0);
		if (!ft_isdigit_str(trim))
			return (free(trim), free_matrix(parts), 0);
		rgb[i] = ft_atoi(trim);
		free(trim);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (free_matrix(parts), 0);
		++i;
	}
	free_matrix(parts);
	return (1);
}

static void	draw_ceiling(int *buf, int pitch, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			buf[y * pitch + x] = color;
			x++;
		}
		y++;
	}
}

static void	draw_floor(int *buf, int pitch, int color)
{
	int	y;
	int	x;

	y = WIN_HEIGHT / 2;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			buf[y * pitch + x] = color;
			x++;
		}
		y++;
	}
}

void	draw_floor_and_ceiling(t_game *g)
{
	int	*buf;
	int	pitch;
	int	top_color;
	int	bot_color;

	buf = (int *)g->img.addr;
	pitch = g->img.line_len / 4;
	top_color = (g->settings.ceiling_rgb[0] << 16)
		| (g->settings.ceiling_rgb[1] << 8) | g->settings.ceiling_rgb[2];
	bot_color = (g->settings.floor_rgb[0] << 16)
		| (g->settings.floor_rgb[1] << 8) | g->settings.floor_rgb[2];
	draw_ceiling(buf, pitch, top_color);
	draw_floor(buf, pitch, bot_color);
}
