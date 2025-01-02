/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:57:05 by iatopchu          #+#    #+#             */
/*   Updated: 2024/11/10 13:57:06 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	valid_key(char *key)
{
	int		i;

	i = -1;
	if (!key[0] || !ft_isalpha(key[0]))
		return (0);
	while (key[++i])
	{
		if (key[i] != '_' && !ft_isalnum(key[i]))
			return (0);
	}
	return (1);
}

int	repeated_key(t_node *node, char *key)
{
	t_node	*temp;

	temp = node;
	while (temp)
	{
		if (same_str(temp->key, key))
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	repeated_val(t_node *node, char *val)
{
	t_node	*temp;

	temp = node;
	while (temp)
	{
		if (same_str(temp->val, val))
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	find_dict_end(t_node *node, t_node **temp)
{
	*temp = node;
	while ((*temp)->next)
	{
		(*temp) = (*temp)->next;
	}
}

int	add_or_update_env(t_node **env, char *key, char *val, t_cmd *cmd)
{
	t_node	*temp_end;

	if (!repeated_key(*env, key))
	{
		find_dict_end(*env, &temp_end);
		add_node(&temp_end, key, val);
		cmd->success_flg = 1;
		return (1);
	}
	else if (!repeated_val(*env, val))
	{
		change_val(*env, key, val);
		cmd->success_flg = 1;
		return (1);
	}
	return (0);
}
