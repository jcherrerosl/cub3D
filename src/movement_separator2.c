/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_separator2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiki <aloiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 21:58:37 by aloiki            #+#    #+#             */
/*   Updated: 2025/06/07 21:59:00 by aloiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_vars1(double *rot, double *angle, double *nx, t_game *g)
{
	*rot = g->rot_speed * g->dt;
	*angle = g->settings.player_angle;
	*nx = g->settings.player_x;
}

void	init_vars2(double *ny, double *step, t_game *g)
{
	*step = g->move_speed * g->dt;
	*ny = g->settings.player_y;
}
