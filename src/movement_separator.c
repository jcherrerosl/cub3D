/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_separator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiki <aloiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 21:50:51 by aloiki            #+#    #+#             */
/*   Updated: 2025/06/07 22:00:52 by aloiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	w_pressed(double *player_x, double *player_y, double angle, double step)
{
	*player_x += cos(angle) * step;
	*player_y += sin(angle) * step;
}

void	s_pressed(double *player_x, double *player_y, double angle, double step)
{
	*player_x -= cos(angle) * step;
	*player_y -= sin(angle) * step;
}

void	d_pressed(double *player_x, double *player_y, double angle, double step)
{
	*player_x += cos(angle + M_PI_2) * step;
	*player_y += sin(angle + M_PI_2) * step;
}

void	a_pressed(double *player_x, double *player_y, double angle, double step)
{
	*player_x += cos(angle - M_PI_2) * step;
	*player_y += sin(angle - M_PI_2) * step;
}
