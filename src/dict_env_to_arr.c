/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_env_to_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:55:38 by iatopchu          #+#    #+#             */
/*   Updated: 2024/11/10 13:55:39 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	same_str(char *str1, char *str2)
{
	int	len1;
	int	len2;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (!ft_strncmp(str1, str2, len1)
		&& len1 == len2)
		return (1);
	return (0);
}

int	env_listlen(t_node *node)
{
	int			len;
	t_node		*temp;

	len = 0;
	temp = node;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}

int	changed_env(t_node *old, t_node *new)
{
	t_node	*temp_old;
	t_node	*temp_new;

	temp_old = old;
	temp_new = new;
	while (temp_old && temp_new)
	{
		if (same_str(temp_new->key, temp_old->key)
			|| same_str(temp_new->val, temp_old->val))
			return (1);
		temp_new = temp_new->next;
		temp_old = temp_old->next;
	}
	return (0);
}

void	fill_arr(t_node *env, char ***arr)
{
	int			i;
	t_node		*temp;
	char		*half;
	char		*line;

	i = 0;
	temp = env;
	line = NULL;
	while (temp)
	{
		half = ft_strjoin(temp->key, "=");
		line = ft_strjoin(half, temp->val);
		if (!half || !line)
			return ;
		(*arr)[i] = line;
		free_protect(half);
		temp = temp->next;
		i++;
	}
	(*arr)[i] = NULL;
}

void	dict_env_to_arr(t_env *env)
{
	int			new_len;
	char		**new_arr;
	t_node		*old_env;

	old_env = arr_to_dict(env->arr);
	if (changed_env(old_env, env->node))
	{
		new_len = env_listlen(env->node);
		new_arr = (char **)malloc((new_len + 1) * sizeof(char *));
		fill_arr(env->node, &new_arr);
		free_arr(env->arr);
		env->arr = new_arr;
	}
	free_list(old_env);
}
