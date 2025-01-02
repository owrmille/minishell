/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:00:48 by iatopchu          #+#    #+#             */
/*   Updated: 2023/11/27 16:00:38 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char	*s, int c)
{
	char	*res;
	char	symbol;
	int		len;

	symbol = c;
	res = (char *)s;
	len = ft_strlen(res);
	while (len >= 0)
	{
		if (*(res + len) == (char)symbol)
			return ((char *)res + len);
		len--;
	}
	return (NULL);
}
