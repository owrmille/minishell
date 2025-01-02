/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:02:19 by iatopchu          #+#    #+#             */
/*   Updated: 2023/11/27 14:09:31 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void	*s, int c, size_t n)
{
	char	*res;
	size_t	i;

	i = 0;
	res = (char *)s;
	while (i < n)
	{
		if ((unsigned char)res[i] == (unsigned char)c)
			return ((void *)(res + i));
		i++;
	}
	return (NULL);
}
