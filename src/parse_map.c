/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:03:11 by juanherr          #+#    #+#             */
/*   Updated: 2025/06/08 10:12:40 by juanherr         ###   ########.fr       */
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
	while (line[i] == ' ' || line[i] == '\t')
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
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

int	in_map(t_settings *s)
{
	int	y;
	char *trimmed;

	y = 0;
	while (!ft_strchr(s->map[y], '1'))
		y++;
	while (s->map[y])
	{
		trimmed = ft_strtrim(s->map[y], " \t\n");
		if (ft_strlen(trimmed) == 0)
		{
			free(trimmed);
			ft_printerror("Map contains empty lines\n");
		}
		if (!ft_strchr(s->map[y], '1') && !ft_strchr(s->map[y], '\n'))
		{
			free(trimmed);
			ft_printerror("Map must be at the end of the map file\n");
		}
		free(trimmed);
		y++;
	}
	if (s->map[y])
		ft_printerror("Map must be at the end of the map file\n");
	return (y);
}

static void	parse_map_chars(t_settings *s)
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

void	check_map_enclosed(t_settings *s)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (s->map[y])
	{
		x = 0;
		c = s->map[y][x];
		while (c)
		{
			if ((c == '0' || ft_strchr("NSEW", c)) && (!s->map[y + 1]
					|| !s->map[y - 1] || x >= (int)ft_strlen(s->map[y + 1])
					|| x >= (int)ft_strlen(s->map[y - 1])
					|| s->map[y - 1][x] == ' ' || s->map[y + 1][x] == ' '
					|| x == 0 || s->map[y][x - 1] == ' '
					|| s->map[y][x + 1] == ' ' || s->map[y][x + 1] == '\0'))
				ft_printerror("Map is not properly enclosed\n");
			x++;
			c = s->map[y][x];
		}
		y++;
	}
	s->enclosed = 1;
}

static void	check_content(int *num, char **str_to_save, char *line,
		char *error_msg)
{
	if (*num > 0)
		ft_printerror(error_msg);
	if (!ft_strchr(line, '\n'))
		ft_printerror("map must end with a newline\n");
	*str_to_save = ft_strtrim(line + 2, " \n");
	(*num)++;
}

static void	check_f_color(char *line, t_settings *s)
{
	if (s->f_num > 0)
		ft_printerror("Duplicate floor color\n");
	if (!ft_strchr(line, '\n'))
		ft_printerror("map must end with a newline\n");
	parse_color(line + 2, s->floor_rgb);
	s->f_num = 1;
}

static void	check_c_color(char *line, t_settings *s)
{
	if (s->c_num > 0)
		ft_printerror("Duplicate ceiling color\n");
	if (!ft_strchr(line, '\n'))
		ft_printerror("Map must end with a newline\n");
	parse_color(line + 2, s->ceiling_rgb);
	s->c_num = 1;
}

static void	find_player(t_settings *s)
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

static void	fill_map(t_settings *s, char ***map, int fd)
{
	int		map_i;
	char	*line;

	line = get_next_line(fd);
	map_i = 0;
	while (line)
	{
		if (ft_strncmp(line, "NO ", 3) == 0)
			check_content(&s->no_num, &s->no, line, "Duplicate NO texture\n");
		else if (ft_strncmp(line, "SO ", 3) == 0)
			check_content(&s->so_num, &s->so, line, "Duplicate SO texture\n");
		else if (ft_strncmp(line, "WE ", 3) == 0)
			check_content(&s->we_num, &s->we, line, "Duplicate WE texture\n");
		else if (ft_strncmp(line, "EA ", 3) == 0)
			check_content(&s->ea_num, &s->ea, line, "Duplicate EA texture\n");
		else if (ft_strncmp(line, "F ", 2) == 0)
			check_f_color(line, s);
		else if (ft_strncmp(line, "C ", 2) == 0)
			check_c_color(line, s);
		else if (1)
			(*map)[map_i++] = ft_strtrim(line, "\n");
		free(line);
		line = get_next_line(fd);
	}
	(*map)[map_i] = NULL;
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
