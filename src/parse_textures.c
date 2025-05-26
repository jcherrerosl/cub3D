/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:33:09 by juanherr          #+#    #+#             */
/*   Updated: 2025/05/26 14:44:51 by juanherr         ###   ########.fr       */
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

void	draw_floor_and_ceiling(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			draw_pixel(&game->img, x, y,
					(game->settings.ceiling_rgb[0] << 16) | (game->settings.ceiling_rgb[1] << 8) | game->settings.ceiling_rgb[2]);
			x++;
		}
		y++;
	}
	y = WIN_HEIGHT / 2;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			draw_pixel(&game->img, x, y,
					(game->settings.floor_rgb[0] << 16) | (game->settings.floor_rgb[1] << 8) | game->settings.floor_rgb[2]);
			x++;
		}
		y++;
	}
}
