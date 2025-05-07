/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hex_low.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:14:26 by juanherr          #+#    #+#             */
/*   Updated: 2024/10/27 11:24:21 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_hex_low(size_t n)
{
	int		len;
	char	*hex_digits;

	len = 0;
	hex_digits = "0123456789abcdef";
	if (n >= 16)
		len += ft_put_hex_low(n / 16);
	len += ft_printchar(hex_digits[n % 16]);
	return (len);
}
