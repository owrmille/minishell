/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_var_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:16:23 by dbisko            #+#    #+#             */
/*   Updated: 2025/01/02 22:05:33 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 1 key found, 0 no key;
int	var_found(char *str, int len)
{
	int	i;

	i = 0;
	if (len == 0)
		return (0);
	while (i < len && str[i] != '\0')
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	if (i == len || str[i] != '=')
		return (0);
	i = 0;
	while (i < len && str[i] != '=')
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*find_val(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (&str[i + 1]);
}

int	key_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	return (i);
}

char	*key_def(char *str)
{
	int		len;
	char	*key;

	len = key_len(str) + 1;
	key = (char *)malloc(len);
	ft_strlcpy(key, str, len);
	return (key);
}

int	key_exists(t_node *list, char *key)
{
	t_node	*temp;

	temp = list;
	while (temp)
	{
		if (same_str(temp->key, key))
			return (1);
		temp = temp->next;
	}
	return (0);
}
