/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:30:13 by juanherr          #+#    #+#             */
/*   Updated: 2025/05/07 15:31:31 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_key(int keycode, void *param)
{
	(void)param;
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int	handle_exit(void *param)
{
	(void)param;
	exit(0);
	return (0);
}
