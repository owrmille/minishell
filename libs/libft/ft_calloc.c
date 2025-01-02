/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:02:47 by iatopchu          #+#    #+#             */
/*   Updated: 2023/11/27 16:06:33 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*allocated_space;
	size_t	total_size;

	total_size = size * count;
	if (size != 0 && total_size / size != count)
		return (NULL);
	allocated_space = malloc(total_size);
	if (!allocated_space)
	{
		return (NULL);
	}
	ft_bzero(allocated_space, total_size);
	return (allocated_space);
}
