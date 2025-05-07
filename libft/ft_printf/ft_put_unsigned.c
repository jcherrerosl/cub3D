/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:14:00 by juanherr          #+#    #+#             */
/*   Updated: 2024/10/27 11:23:44 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_unsigned(unsigned int n)
{
	int	len;

	len = 0;
	if (n >= 10)
	{
		len += ft_put_unsigned(n / 10);
	}
	len += ft_printchar((n % 10) + '0');
	return (len);
}
