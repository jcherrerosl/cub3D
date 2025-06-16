/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:12:40 by juanherr          #+#    #+#             */
/*   Updated: 2025/06/16 01:43:15 by juanherr         ###   ########.fr       */
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
					|| x >= (int)ft_strlen(s->map[y - 1]) || s->map[y
						- 1][x] == ' ' || s->map[y + 1][x] == ' ' || x == 0
					|| s->map[y][x - 1] == ' ' || s->map[y][x + 1] == ' '
					|| s->map[y][x + 1] == '\0'))
				ft_exit_error("Map is not properly enclosed\n", s, s->map);
			x++;
			c = s->map[y][x];
		}
		y++;
	}
	s->enclosed = 1;
}

void	check_content(int *num, char **str_to_save, char *line, char *error_msg)
{
	if (*num > 0)
		ft_exit_error(error_msg, NULL, NULL);
	if (!ft_strchr(line, '\n'))
		ft_exit_error("map must end with a newline\n", NULL, NULL);
	*str_to_save = ft_strtrim(line + 2, " \n");
	if (!*str_to_save)
		ft_exit_error("Memory allocation failed\n", NULL, NULL);
	(*num)++;
}

void	check_f_color(char *line, t_settings *s)
{
	if (s->f_num > 0)
		ft_exit_error("Duplicate floor color\n", s, NULL);
	if (!ft_strchr(line, '\n'))
		ft_exit_error("map must end with a newline\n", s, NULL);
	parse_color(line + 2, s->floor_rgb);
	s->f_num = 1;
}

void	check_c_color(char *line, t_settings *s)
{
	if (s->c_num > 0)
		ft_exit_error("Duplicate ceiling color\n", s, NULL);
	if (!ft_strchr(line, '\n'))
		ft_exit_error("map must end with a newline\n", s, NULL);
	parse_color(line + 2, s->ceiling_rgb);
	s->c_num = 1;
}
