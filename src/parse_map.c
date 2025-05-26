/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:03:11 by juanherr          #+#    #+#             */
/*   Updated: 2025/05/26 15:55:32 by juanherr         ###   ########.fr       */
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

static int	count_map_lines(const char *filename)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
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

static void	parse_map_chars(t_settings *s)
{
	int	y;
	int	x;
	char	c;

	y = 0;
	while (s->map[y])
	{
		x = 0;
		while ((c = s->map[y][x]))
		{
			if (c != '1' && c != '0' && c != ' ' && !ft_strchr("NSEW", c))
			{
				printf("Invalid character '%c' at (%d, %d)\n", c, x, y);
				ft_printerror("Invalid character in map\n");
			}
			x++;
		}
		y++;
	}
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
		else if (ft_strncmp(line, "F ", 2) == 0)
			parse_color(line + 2, s->floor_rgb);
		else if (ft_strncmp(line, "C ", 2) == 0)
			parse_color(line + 2, s->ceiling_rgb);
		else if (is_map_line(line))
			map[map_i++] = ft_strtrim(line, "\n");
		free(line);
		line = get_next_line(fd);
	}
	map[map_i] = NULL;
	close(fd);
	s->map = map;
	parse_map_chars(s);
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

void    check_walls(t_settings *s)
{
	int y;
	int x;

	y = 0;
	while (s->map[y])
	{
		x = 0;
		while (s->map[y][x])
		{
			if (s->map[y][x] == '1')
			{
				if ((y == 0 || !s->map[y - 1] || s->map[y - 1][x] != '1') ||
					(s->map[y + 1] && s->map[y + 1][x] != '1') ||
					(x == 0 || s->map[y][x - 1] != '1') ||
					(s->map[y][x + 1] && s->map[y][x + 1] != '1'))
				{
					ft_printerror("Map is not surrounded by walls\n");
				}
			}
			x++;
		}
		y++;
	}
}
