/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:11:24 by juanherr          #+#    #+#             */
/*   Updated: 2025/06/06 18:12:40 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_textures	*init_data_add(t_textures *textures)
{
	textures->no_data = mlx_get_data_addr(textures->no, &textures->bpp,
			&textures->line_len, &textures->endian);
	textures->so_data = mlx_get_data_addr(textures->so, &textures->bpp,
			&textures->line_len, &textures->endian);
	textures->we_data = mlx_get_data_addr(textures->we, &textures->bpp,
			&textures->line_len, &textures->endian);
	textures->ea_data = mlx_get_data_addr(textures->ea, &textures->bpp,
			&textures->line_len, &textures->endian);
	if (!textures->no_data || !textures->so_data || !textures->we_data
		|| !textures->ea_data)
		ft_printerror("Could not get data address for textures");
	return (textures);
}

t_textures	*init_textures(t_game *game)
{
	t_textures	*textures;

	textures = malloc(sizeof(t_textures));
	if (!textures)
		ft_printerror("Could not allocate memory for textures");
	textures->width = 256;
	textures->height = 256;
	textures->no = mlx_xpm_file_to_image(game->img.mlx, game->settings.no,
			&textures->width, &textures->height);
	textures->so = mlx_xpm_file_to_image(game->img.mlx, game->settings.so,
			&textures->width, &textures->height);
	textures->we = mlx_xpm_file_to_image(game->img.mlx, game->settings.we,
			&textures->width, &textures->height);
	textures->ea = mlx_xpm_file_to_image(game->img.mlx, game->settings.ea,
			&textures->width, &textures->height);
	if (!textures->no || !textures->so || !textures->we || !textures->ea)
		ft_printerror("Could not load textures");
	textures = init_data_add(textures);
	return (textures);
}
