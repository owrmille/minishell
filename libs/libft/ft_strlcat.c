/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:01:15 by iatopchu          #+#    #+#             */
/*   Updated: 2023/11/28 00:17:50 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char	*dst, const char	*src, size_t dstsize)
{
	size_t	i;
	size_t	dst_fixed_len;

	i = 0;
	while (dst[i] && i < dstsize)
		i++;
	dst_fixed_len = i;
	i = 0;
	while (src[i] && (dst_fixed_len + i +1) < dstsize)
	{
		dst[dst_fixed_len + i] = src[i];
		i++;
	}
	if (dst_fixed_len < dstsize)
		dst[dst_fixed_len + i] = '\0';
	return (dst_fixed_len + ft_strlen(src));
}
