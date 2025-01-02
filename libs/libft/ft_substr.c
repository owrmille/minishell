/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:00:35 by iatopchu          #+#    #+#             */
/*   Updated: 2024/01/15 21:42:01 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;
	size_t	subs_len;

	if (NULL == s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (NULL);
	subs_len = s_len - start;
	if (len > subs_len)
		len = subs_len;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (NULL == str)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}
