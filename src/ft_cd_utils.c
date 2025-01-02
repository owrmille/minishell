/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:56:38 by iatopchu          #+#    #+#             */
/*   Updated: 2024/11/10 13:56:39 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*get_val(t_node *node, char *key)
{
	while (node && node->key)
	{
		if (same_str(node->key, key))
		{
			return (node->val);
		}
		node = node->next;
	}
	return (NULL);
}

void	change_val(t_node *node, char *key, char *new_val)
{
	while (node && node->key)
	{
		if (same_str(node->key, key))
		{
			if (node->val)
			{
				free(node->val);
				node->val = NULL;
			}
			node->val = ft_strdup(new_val);
			break ;
		}
		node = node->next;
	}
}

int	are_too_many_arguments(t_cmd *cmd)
{
	if (ft_arrlen(cmd->cmd_args) > 1)
	{
		cmd->exit_stat = 1;
		ft_putendl_fd("cd: too many arguments", 2);
		return (1);
	}
	return (0);
}
