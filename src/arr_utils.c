/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:14:58 by dbisko            #+#    #+#             */
/*   Updated: 2024/11/12 12:15:00 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	arr_len(char **arr)
{
	int	index;

	index = 0;
	if (!arr)
		return (0);
	while (arr[index])
		index++;
	return (index);
}

void	*ft_realloc(void *ptr, int old_size, int new_size)
{
	void	*new_ptr;
	int		copy_size;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
}

char	*ft_strncat(char *dest, char *src, int n)
{
	char	*dest_end;
	int		i;

	dest_end = dest + ft_strlen(dest);
	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest_end[i] = src[i];
		++i;
	}
	dest_end[i] = '\0';
	return (dest);
}
