/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:17:33 by iatopchu          #+#    #+#             */
/*   Updated: 2024/01/20 19:17:34 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_type(char type, va_list args)
{
	int	printed_chars;

	printed_chars = 0;
	if (type == 'c')
		printed_chars += ft_print_c(va_arg(args, int));
	else if (type == 's')
		printed_chars += ft_print_s(va_arg(args, char *));
	else if (type == 'd' || type == 'i')
		printed_chars += ft_print_d(va_arg(args, int));
	else if (type == 'x' || type == 'X')
		printed_chars += ft_print_x(va_arg(args, unsigned int), type);
	else if (type == 'p')
		printed_chars += ft_print_p(va_arg(args, unsigned long));
	else if (type == 'u')
		printed_chars += ft_print_u(va_arg(args, unsigned int));
	else if (type == '%')
		return (write(1, "%", 1));
	return (printed_chars);
}
