/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:18:06 by iatopchu          #+#    #+#             */
/*   Updated: 2024/01/29 22:55:05 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_x(unsigned int n, int letter_case)
{
	char	*system;

	system = NULL;
	if (letter_case == 'x')
		system = "0123456789abcdef";
	else if (letter_case == 'X')
		system = "0123456789ABCDEF";
	return (ft_hexadec_nbr(n, system));
}
