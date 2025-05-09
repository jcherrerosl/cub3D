/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:03:11 by juanherr          #+#    #+#             */
/*   Updated: 2025/05/09 03:35:44 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extension(const char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	return (ft_strncmp(filename + len - 4, ".cub", 4) == 0);
}

int	is_map_line(char *line)
{
	while (*line == ' ')
		line++;
	return (*line == '1' || *line == '0' || ft_strchr("NSEW", *line));
}

void	store_player(t_settings *s, int x, int y, char dir)
{
	s->player_x = x;
	s->player_y = y;
	s->player_dir = dir;
	s->map[y][x] = '0';
}

void	parse_file(const char *filename, t_settings *s)
{
	int		fd = open(filename, O_RDONLY);
	char	*line;
	char	**map = malloc(sizeof(char *) * 128); // ajusta tamaño si hace falta
	int		map_i = 0;

	if (fd < 0 || !map)
		exit(1);
	while ((line = get_next_line(fd)))
	{
		if (ft_strncmp(line, "NO ", 3) == 0)
			s->no = ft_strtrim(line + 2, " \n");
		else if (ft_strncmp(line, "SO ", 3) == 0)
			s->so = ft_strtrim(line + 2, " \n");
		else if (ft_strncmp(line, "WE ", 3) == 0)
			s->we = ft_strtrim(line + 2, " \n");
		else if (ft_strncmp(line, "EA ", 3) == 0)
			s->ea = ft_strtrim(line + 2, " \n");
		else if (ft_strncmp(line, "F ", 2) == 0)
			; // parse_floor_color(line + 1); // puedes hacerlo luego
		else if (ft_strncmp(line, "C ", 2) == 0)
			; // parse_ceiling_color(line + 1);
		else if (is_map_line(line))
			map[map_i++] = ft_strtrim(line, "\n");
		free(line);
	}
	map[map_i] = NULL;
	close(fd);
	s->map = map;

	// detectar jugador
	int y = 0, x;
	while (s->map[y])
	{
		x = 0;
		while (s->map[y][x])
		{
			char c = s->map[y][x];
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
