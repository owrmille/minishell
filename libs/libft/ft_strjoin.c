/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:01:20 by iatopchu          #+#    #+#             */
/*   Updated: 2023/11/27 14:18:49 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const	*s1, char const	*s2)
{
	char	*draft_res;
	char	*res;
	int		total_len;

	if (!s1 && !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	draft_res = (char *)malloc((total_len + 1) * sizeof(char));
	if (!draft_res)
		return (NULL);
	res = draft_res;
	while (*s1)
	{
		*draft_res++ = *s1++;
	}
	while (*s2)
	{
		*draft_res++ = *s2++;
	}
	*draft_res = '\0';
	return (res);
}
