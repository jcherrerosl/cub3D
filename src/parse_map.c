/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:03:11 by juanherr          #+#    #+#             */
/*   Updated: 2025/05/07 17:16:14 by juanherr         ###   ########.fr       */
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

int	map_line_count(int fd)
{
	char	*line;
	int		count;

	count = 1;
	while ((line = get_next_line(fd)))
	{
		if (line[0] == '\n')
		{
			free(line);
			break ;
		}
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

void	parse_map(int fd, char *first_line, t_settings *s)
{
	int		count;
	char	**map;
	char	*line;
	int		i;

	count = map_line_count(fd);
	fd = open(s->no, O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		if (line[0] == '1' || line[0] == '0' || ft_strchr("NSEW", line[0]))
			break ;
		free(line);
	}
	map = malloc(sizeof(char *) * (count + 1));
	if (!map)
		return ;
	i = 0;
	map[i++] = ft_strdup(first_line);
	free(first_line);
	while (i < count && (line = get_next_line(fd)))
	{
		map[i] = ft_strdup(line);
		free(line);
		i++;
	}
	map[i] = NULL;
	s->map = map;
	close(fd);
}
