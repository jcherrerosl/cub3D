/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hex_upp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:14:16 by juanherr          #+#    #+#             */
/*   Updated: 2024/10/27 11:24:28 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_hex_upp(size_t n)
{
	int		len;
	char	*hex_digits;

	len = 0;
	hex_digits = "0123456789ABCDEF";
	if (n >= 16)
		len += ft_put_hex_upp(n / 16);
	len += ft_printchar(hex_digits[n % 16]);
	return (len);
}
