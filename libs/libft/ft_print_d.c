/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:17:47 by iatopchu          #+#    #+#             */
/*   Updated: 2024/01/20 19:19:35 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_d(int n)
{
	int	printed_digit;
	int	new_nb;
	int	printed_chars;

	printed_chars = 0;
	if (n == -2147483648)
		printed_chars += write(1, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			printed_chars += write(1, "-", 1);
			n *= -1;
		}
		new_nb = n;
		if (new_nb / 10 != 0)
			printed_chars += ft_print_d(new_nb / 10);
		printed_digit = (new_nb % 10) + '0';
		printed_chars += write(1, &printed_digit, 1);
	}
	return (printed_chars);
}
