/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:02:08 by iatopchu          #+#    #+#             */
/*   Updated: 2023/11/27 14:10:39 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void	*dst, const void	*src, size_t len)
{
	size_t	i;

	if (src != dst)
	{
		if (src < dst)
		{
			i = len;
			while (i > 0)
			{
				i--;
				((char *)dst)[i] = ((char *)src)[i];
			}
		}
		else
		{
			ft_memcpy(dst, src, len);
		}
	}
	return (dst);
}
