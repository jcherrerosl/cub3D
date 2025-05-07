/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:33:33 by aloiki            #+#    #+#             */
/*   Updated: 2025/04/22 14:57:33 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_matrix_dup(char **matrix)
{
	int		i;
	char	**dup_matrix;

	i = 0;
	if (!matrix)
		return (NULL);
	dup_matrix = (char **)malloc(sizeof(char *) * (ft_matrix_len(matrix) + 1));
	while (matrix[i])
	{
		dup_matrix[i] = ft_strdup(matrix[i]);
		i++;
	}
	dup_matrix[i] = NULL;
	return (dup_matrix);
}
