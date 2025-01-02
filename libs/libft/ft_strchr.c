/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:01:37 by iatopchu          #+#    #+#             */
/*   Updated: 2023/11/27 14:16:50 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char	*s, int c)
{
	char	*res;
	char	symbol;

	symbol = c;
	res = (char *)s;
	while (*res != symbol)
	{
		if (*res == '\0')
			return (NULL);
		res++;
	}
	return (res);
}
