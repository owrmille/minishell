/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexadec_nbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:17:38 by iatopchu          #+#    #+#             */
/*   Updated: 2024/01/20 19:19:13 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexadec_nbr(unsigned long n, char *system)
{
	int	printed_digit;
	int	printed_chars;

	printed_chars = 0;
	if (n / 16 != 0)
	{
		printed_chars += ft_hexadec_nbr(n / 16, system);
	}
	printed_digit = system[n % 16];
	printed_chars += ft_print_c(printed_digit);
	return (printed_chars);
}
