/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:49:23 by juanherr          #+#    #+#             */
/*   Updated: 2025/05/07 16:29:35 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_color(char *line, int *rgb)
{
	char	**parts;
	int		i;

	parts = ft_split(line, ',');
	if (!parts)
		return ;
	i = 0;
	while (i < 3 && parts[i])
	{
		rgb[i] = ft_atoi(parts[i]);
		i++;
	}
	while (i < 3)
		rgb[i++] = 0;
	i = 0;
	while (parts[i])
		free(parts[i++]);
	free(parts);
}

void	parse_line(char *line, t_settings *s)
{
	while (*line == ' ')
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		s->no = ft_strtrim(line + 3, " \n");
	else if (ft_strncmp(line, "SO ", 3) == 0)
		s->so = ft_strtrim(line + 3, " \n");
	else if (ft_strncmp(line, "WE ", 3) == 0)
		s->we = ft_strtrim(line + 3, " \n");
	else if (ft_strncmp(line, "EA ", 3) == 0)
		s->ea = ft_strtrim(line + 3, " \n");
	else if (ft_strncmp(line, "F ", 2) == 0)
		parse_color(line + 2, s->floor_rgb);
	else if (ft_strncmp(line, "C ", 2) == 0)
		parse_color(line + 2, s->ceiling_rgb);
}

void	parse_file(const char *filename, t_settings *s)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error al abrir el archivo");
		exit(1);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (*line == '1' || *line == '0' || ft_strchr("NSEW", *line))
		{
			parse_map(fd, line, s);
			break ;
		}
		else
			parse_line(line, s);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
