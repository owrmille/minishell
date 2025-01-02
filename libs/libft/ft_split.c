/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:01:42 by iatopchu          #+#    #+#             */
/*   Updated: 2023/11/28 14:55:25 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const	*s, char c)
{
	int	words_cnt;
	int	i;
	int	prev_del;

	words_cnt = 0;
	prev_del = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			prev_del = 1;
		else if (prev_del == 1)
			words_cnt++;
		if (s[i] != c)
			prev_del = 0;
		i++;
	}
	return (words_cnt);
}

static int	protect_malloc(char	**words_v, int position, size_t buffer)
{
	int	i;

	i = 0;
	words_v[position] = malloc(buffer);
	if (words_v[position] == NULL)
	{
		while (i < position)
		{
			free(words_v[i]);
			i++;
		}
		free(words_v);
		return (1);
	}
	return (0);
}

static int	fill_v(char	**words_v, char const	*s, char c)
{
	int		position;
	size_t	len;

	position = 0;
	while (*s)
	{
		len = 0;
		while (*s && *s == c)
			s++;
		while (*s && *s != c)
		{
			len++;
			s++;
		}
		if (len != 0)
		{
			if (protect_malloc(words_v, position, len + 1))
				return (1);
			ft_strlcpy(words_v[position], s - len, len + 1);
		}
		position++;
	}
	return (0);
}

char	**ft_split(char const	*s, char c)
{
	int		words_cnt;
	char	**words_v;

	if (s == NULL)
		return (NULL);
	words_cnt = count_words(s, c);
	words_v = malloc((words_cnt + 1) * sizeof(char *));
	if (words_v == NULL)
		return (NULL);
	words_v[words_cnt] = NULL;
	if (fill_v(words_v, s, c))
		return (NULL);
	return (words_v);
}
