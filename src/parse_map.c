/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:03:11 by juanherr          #+#    #+#             */
/*   Updated: 2025/06/16 01:37:41 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	store_player(t_settings *s, int x, int y, char dir)
{
	s->player_x = x + 0.5;
	s->player_y = y + 0.5;
	if (dir == 'N')
		s->player_angle = 3 * M_PI / 2;
	else if (dir == 'S')
		s->player_angle = M_PI / 2;
	else if (dir == 'E')
		s->player_angle = 0;
	else if (dir == 'W')
		s->player_angle = M_PI;
	s->map[y][x] = '0';
}

void	parse_map_chars(t_settings *s)
{
	int		y;
	int		x;
	char	c;
	int		player_count;

	y = 0;
	player_count = 0;
	while (s->map[y])
	{
		x = 0;
		c = s->map[y][x];
		while (c)
		{
			if (c != '1' && c != '0' && c != ' ' && !ft_strchr("NSEW", c))
				ft_printerror("Invalid character in map\n");
			if (ft_strchr("NSEW", c))
				player_count++;
			x++;
			c = s->map[y][x];
		}
		y++;
	}
	if (player_count != 1)
		ft_printerror("Map must have exactly one player\n");
}

void	find_player(t_settings *s)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (s->map[y])
	{
		x = 0;
		while (s->map[y][x])
		{
			c = s->map[y][x];
			if (ft_strchr("NSEW", c))
			{
				if (c == 'N' && s->map[y][x + 1] == 'O')
					break ;
				store_player(s, x, y, c);
				return ;
			}
			x++;
		}
		y++;
	}
}

void	parse_file(const char *filename, t_settings *s)
{
	int		fd;
	char	**map;

	fd = open(filename, O_RDONLY);
	map = malloc(sizeof(char *) * (count_map_lines(filename) + 1));
	if (fd < 0 || !map)
		ft_printerror("Error opening file\n");
	fill_map(s, &map, fd);
	if (s->f_num != 1 || s->c_num != 1 || s->no_num != 1 || s->so_num != 1
		|| s->we_num != 1 || s->ea_num != 1)
		ft_printerror("Missing texture/color definitions\n");
	close(fd);
	s->map = map;
	in_map(s);
	parse_map_chars(s);
	check_map_enclosed(s);
	find_player(s);
}
