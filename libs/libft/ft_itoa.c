/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:02:23 by iatopchu          #+#    #+#             */
/*   Updated: 2023/11/28 14:46:51 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	length_val(int val)
{
	int	len;

	len = 0;
	if (val == 0)
		return (1);
	else if (val < 0)
		len++;
	val *= -1;
	while (val != 0)
	{
		val /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	len = length_val(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (len)
	{
		if (n < 0)
			str[0] = '-';
		else if (n == 0)
			str[0] = '0';
		while (n != 0)
		{
			if (n > 0)
				str[--len] = n % 10 + '0';
			else if (n < 0)
				str[--len] = -(n % 10) + '0';
			n /= 10;
		}
	}
	return (str);
}
