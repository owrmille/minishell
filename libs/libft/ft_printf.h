/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:18:16 by iatopchu          #+#    #+#             */
/*   Updated: 2024/01/29 22:56:05 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include "libft.h"

int	ft_printf(const char *content_str, ...);
int	ft_check_type(char type, va_list args);
int	ft_print_c(int c);
int	ft_print_s(char *s);
int	ft_print_d(int n);
int	ft_hexadec_nbr(unsigned long n, char *system);
int	ft_print_x(unsigned int n, int letter_case);
int	ft_print_p(unsigned long ptr_adress);
int	ft_print_u(unsigned int n);

#endif