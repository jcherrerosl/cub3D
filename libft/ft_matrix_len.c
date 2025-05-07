/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:35:10 by aloiki            #+#    #+#             */
/*   Updated: 2025/04/22 14:57:33 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_matrix_len(char **matrix)
{
	int	i;

	if (!matrix)
		return (0);
	i = 0;
	while (matrix[i])
		i++;
	return (i);
}
