/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:03:11 by juanherr          #+#    #+#             */
/*   Updated: 2025/05/09 13:17:19 by juanherr         ###   ########.fr       */
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
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	return (line[i] == '1' || line[i] == '0' || ft_strchr("NSEW", line[i]));
}


void	store_player(t_settings *s, int x, int y, char dir)
{
	s->player_x = x;
	s->player_y = y;
	s->player_dir = dir;
	s->map[y][x] = '0';
}

static int	count_map_lines(const char *filename)
{
	int		fd;
	char	*line;
	int		count = 0;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		if (is_map_line(line))
			count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}


void	parse_file(const char *filename, t_settings *s)
{
	int		fd;
	char	*line;
	char	**map;
	int		map_i;
	int		x;
	int		y;
	char	c;

	fd = open(filename, O_RDONLY);
	map = malloc(sizeof(char *) * (count_map_lines(filename) + 1));
	if (fd < 0 || !map)
		ft_printerror("Error opening file\n");
	map_i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, "NO ", 3) == 0)
			s->no = ft_strtrim(line + 2, " \n");
		else if (ft_strncmp(line, "SO ", 3) == 0)
			s->so = ft_strtrim(line + 2, " \n");
		else if (ft_strncmp(line, "WE ", 3) == 0)
			s->we = ft_strtrim(line + 2, " \n");
		else if (ft_strncmp(line, "EA ", 3) == 0)
			s->ea = ft_strtrim(line + 2, " \n");
		// else if (ft_strncmp(line, "F ", 2) == 0)
		// 	; // parse_floor_color(line + 1);
		// else if (ft_strncmp(line, "C ", 2) == 0)
		// 	; // parse_ceiling_color(line + 1);
		else if (is_map_line(line))
			map[map_i++] = ft_strtrim(line, "\n");
		free(line);
		line = get_next_line(fd);
	}
	map[map_i] = NULL;
	close(fd);
	s->map = map;
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
