/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:03:11 by juanherr          #+#    #+#             */
/*   Updated: 2025/06/06 18:03:15 by juanherr         ###   ########.fr       */
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

	// y = 0;
	// while (s->map[y])
	// {
	// 	printf("Map line %d: %s\n", y, s->map[y]);
	// 	y++;
	// }
	y = 0;
	while (!ft_strchr(s->map[y], '1'))
		y++;
	while (s->map[y])
	{
		if (!ft_strchr(s->map[y], '1') && !ft_strchr(s->map[y], '\n'))
			ft_printerror("Map must be at the end of the map file\n");
		else if (!ft_strchr(s->map[y], '1'))
		{
			ft_printerror("Map contains empty lines\n");
		}
	//	printf("Map line %d: %s\n", y, s->map[y]);
		y++;
	}
	//printf("Map ends at line %d\n", y - 1);
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
		while ((c = s->map[y][x]))
		{
			if (c != '1' && c != '0' && c != ' ' && !ft_strchr("NSEW", c))
				ft_printerror("Invalid character in map\n");
			if (ft_strchr("NSEW", c))
				player_count++;
			x++;
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
		while ((c = s->map[y][x]))
		{
			if (c == '0' || ft_strchr("NSEW", c))
			{
				if (!s->map[y + 1] || !s->map[y - 1]
					|| x >= (int)ft_strlen(s->map[y + 1])
					|| x >= (int)ft_strlen(s->map[y - 1]) || s->map[y
					- 1][x] == ' ' || s->map[y + 1][x] == ' ' || x == 0
					|| s->map[y][x - 1] == ' ' || s->map[y][x + 1] == ' '
					|| s->map[y][x + 1] == '\0')
					ft_printerror("Map is not properly enclosed\n");
			}
			x++;
		}
		y++;
	}
	s->enclosed = 1;
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
		{
			if (s->no_num > 0)
				ft_printerror("Duplicate NO texture\n");
			if (!ft_strchr(line, '\n'))
				ft_printerror("map must end with a newline\n");
			s->no = ft_strtrim(line + 2, " \n");
			s->no_num++;
		}
		else if (ft_strncmp(line, "SO ", 3) == 0)
		{
			if (s->so_num > 0)
				ft_printerror("Duplicate SO texture\n");
			if (!ft_strchr(line, '\n'))
				ft_printerror("map must end with a newline\n");
			s->so = ft_strtrim(line + 2, " \n");
			s->so_num++;
		}
		else if (ft_strncmp(line, "WE ", 3) == 0)
		{
			if (s->we_num > 0)
				ft_printerror("Duplicate WE texture\n");
			if (!ft_strchr(line, '\n'))
				ft_printerror("map must end with a newline\n");
			s->we = ft_strtrim(line + 2, " \n");
			s->we_num++;
		}
		else if (ft_strncmp(line, "EA ", 3) == 0)
		{
			if (s->ea_num > 0)
				ft_printerror("Duplicate EA texture\n");
			if (!ft_strchr(line, '\n'))
				ft_printerror("map must end with a newline\n");
			s->ea = ft_strtrim(line + 2, " \n");
			s->ea_num++;
		}
		else if (ft_strncmp(line, "F ", 2) == 0)
		{
			if (s->f_num > 0)
				ft_printerror("Duplicate floor color\n");
			if (!ft_strchr(line, '\n'))
				ft_printerror("map must end with a newline\n");
			parse_color(line + 2, s->floor_rgb);
			s->f_num = 1;
		}
		else if (ft_strncmp(line, "C ", 2) == 0)
		{
			if (s->c_num > 0)
				ft_printerror("Duplicate ceiling color\n");
			if (!ft_strchr(line, '\n'))
				ft_printerror("map must end with a newline\n");
			parse_color(line + 2, s->ceiling_rgb);
			s->c_num = 1;
		}
		else if (1)
		{
			map[map_i++] = ft_strtrim(line, "\n");
		}
		free(line);
		line = get_next_line(fd);
	}
	if (s->f_num != 1 || s->c_num != 1 || s->no_num != 1 || s->so_num != 1
		|| s->we_num != 1 || s->ea_num != 1)
		ft_printerror("Missing texture/color definitions\n");
	map[map_i] = NULL;
	close(fd);
	s->map = map;
	in_map(s);
	parse_map_chars(s);
	check_map_enclosed(s);
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
