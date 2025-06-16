/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:14:20 by juanherr          #+#    #+#             */
/*   Updated: 2025/06/16 01:58:11 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_map_lines(const char *filename)
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
	int		y;
	char	*trimmed;

	y = 0;
	while (s->map[y] && !ft_strchr(s->map[y], '1'))
		y++;
	while (s->map[y])
	{
		trimmed = ft_strtrim(s->map[y], " \t\n");
		if (!trimmed)
			ft_exit_error("malloc failed in in_map\n", s, s->map);
		if (ft_strlen(trimmed) == 0)
		{
			free(trimmed);
			ft_exit_error("Map contains empty lines\n", s, s->map);
		}
		if (!ft_strchr(s->map[y], '1') && !ft_strchr(s->map[y], '\n'))
		{
			free(trimmed);
			ft_exit_error("Map must be at the end\n", s, s->map);
		}
		free(trimmed);
		y++;
	}
	return (y);
}

static void	parse_line(t_settings *s, char *line, char ***map, int *map_i)
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
	else
	{
		(*map)[*map_i] = ft_strtrim(line, " \t\n");
		if (!(*map)[*map_i])
			ft_exit_error("Malloc failed in map line", s, *map);
		(*map_i)++;
	}
}

void	fill_map(t_settings *s, char ***map, int fd)
{
	int		map_i;
	char	*line;

	map_i = 0;
	line = get_next_line(fd);
	while (line)
	{
		parse_line(s, line, map, &map_i);
		free(line);
		line = get_next_line(fd);
	}
	(*map)[map_i] = NULL;
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (line[i] == '1' || line[i] == '0' || ft_strchr("NSEW", line[i]));
}
