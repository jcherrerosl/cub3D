/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:34:23 by juanherr          #+#    #+#             */
/*   Updated: 2025/06/16 01:57:13 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isdigit_str(char *s)
{
	int	i;

	i = 0;
	if (!s || !*s)
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

double	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0);
}

void	ft_exit_error(char *msg, t_settings *s, char **map)
{
	if (map)
		free_matrix(map);
	if (s)
	{
		if (s->no)
			free(s->no);
		if (s->so)
			free(s->so);
		if (s->we)
			free(s->we);
		if (s->ea)
			free(s->ea);
	}
	ft_putstr_fd("Error\n\t", 2);
	ft_putstr_fd(msg, 2);
	exit(1);
}
