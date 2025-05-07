/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:13:47 by juanherr          #+#    #+#             */
/*   Updated: 2024/10/27 11:23:33 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printnbr(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
	{
		return (ft_putstr("-2147483648"));
	}
	if (n < 0)
	{
		len += ft_printchar('-');
		n = -n;
	}
	if (n >= 10)
	{
		len += ft_printnbr(n / 10);
	}
	len += ft_printchar((n % 10) + '0');
	return (len);
}
