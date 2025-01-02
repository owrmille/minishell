/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:15:37 by dbisko            #+#    #+#             */
/*   Updated: 2024/11/12 12:15:38 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substrdup(const char *start, size_t len)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	while (i < len)
	{
		dest[i] = start[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	cnt_tkns(t_token *tokens)
{
	int	index;
	int	count;

	count = 0;
	index = 0;
	while (tokens[index].type != NULL)
	{
		count++;
		index++;
	}
	return (count);
}

int	is_key(char *env_var, char *key)
{
	while (*env_var == *key && *env_var != '=' && *key != '\0')
	{
		env_var++;
		key++;
	}
	if (*key == '\0' && *env_var == '=')
		return (1);
	return (0);
}

t_env	*init_env(char **l_env)
{
	t_env	*env_node;

	env_node = (t_env *)malloc(sizeof(t_env));
	if (!env_node)
		return (NULL);
	env_node->arr = l_env;
	env_node->node = arr_to_dict(l_env);
	return (env_node);
}
