/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:18:02 by iatopchu          #+#    #+#             */
/*   Updated: 2024/01/20 19:20:06 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_u(unsigned int n)
{
	int	printed_digit;
	int	printed_chars;

	printed_chars = 0;
	if (n / 10 != 0)
	{
		printed_chars += ft_print_u(n / 10);
	}
	printed_digit = (n % 10) + '0';
	printed_chars += write(1, &printed_digit, 1);
	return (printed_chars);
}
