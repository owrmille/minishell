/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:02:15 by iatopchu          #+#    #+#             */
/*   Updated: 2023/11/27 14:10:06 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void	*s1, const void	*s2, size_t n)
{
	char	*c_s1;
	char	*c_s2;
	size_t	i;

	c_s1 = (char *)s1;
	c_s2 = (char *)s2;
	i = 0;
	if (n == 0)
	{
		return (0);
	}
	while ((c_s1[i] == c_s2[i]) && (i < n - 1))
		i++;
	return ((unsigned char)c_s1[i] - (unsigned char)c_s2[i]);
}
