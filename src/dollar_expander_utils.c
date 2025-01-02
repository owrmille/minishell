/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expander_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:55:45 by iatopchu          #+#    #+#             */
/*   Updated: 2024/11/10 13:56:05 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	find_non_key_val(char *str, int j)
{
	if (str[j] && str[j] == '?')
		return (j + 1);
	while (str[j])
	{
		if (!iskey(str[j]))
			break ;
		j++;
	}
	return (j);
}

char	*extract_key(char *str, int start, int end)
{
	char	*key;

	if (str[start] && str[start] == '?')
		key = ft_strdup("?");
	else
		key = ft_substr(str, start, end - start + 1);
	return (key);
}

char	*append_val(char *key, t_info *d, char **new_str)
{
	char	*val;
	char	*temp;

	val = NULL;
	temp = NULL;
	if (same_str(key, "?"))
	{
		val = ft_itoa(d->exit_status);
		if (!val)
			return (NULL);
		temp = ft_strjoin(*new_str, val);
		free(val);
	}
	else
	{
		val = get_val(d->env, key);
		if (!val)
			val = get_val(d->lv, key);
		if (val)
			temp = ft_strjoin(*new_str, val);
	}
	return (temp);
}

int	put_val(char **new_str, char *str, t_info *d, int start)
{
	char	*key;
	char	*temp;
	int		end;

	end = find_non_key_val(str, start) - 1;
	key = extract_key(str, start, end);
	if (!key)
		return (-2);
	temp = append_val(key, d, new_str);
	if (temp)
	{
		free_protect(*new_str);
		*new_str = temp;
	}
	else
	{
		free_protect(key);
		return (-2);
	}
	free_protect(key);
	return (end);
}

char	*append_filling(char *new_str, char *str, int end_key, int i)
{
	char	*temp;
	char	*filling;

	filling = ft_substr(str, end_key + 1, i - end_key - 1);
	if (!filling)
	{
		free_protect(new_str);
		return (NULL);
	}
	temp = ft_strjoin(new_str, filling);
	free_protect(filling);
	free_protect(new_str);
	if (!temp)
		return (NULL);
	return (temp);
}
