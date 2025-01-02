/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:18:11 by iatopchu          #+#    #+#             */
/*   Updated: 2024/01/21 14:23:29 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *content_str, ...)
{
	int		printed_chars;
	int		i;
	va_list	args;

	printed_chars = 0;
	i = 0;
	if (!content_str)
		return (-1);
	va_start(args, content_str);
	while (content_str[i])
	{
		if (content_str[i] == '%')
			printed_chars += ft_check_type(content_str[++i], args);
		else
			printed_chars += ft_print_c(content_str[i]);
		i++;
	}
	va_end(args);
	return (printed_chars);
}
