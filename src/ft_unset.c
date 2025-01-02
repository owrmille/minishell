/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:57:21 by iatopchu          #+#    #+#             */
/*   Updated: 2024/11/10 13:57:22 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	remove_node(t_node **head, char *key_toremove)
{
	t_node	*temp;
	t_node	*moving_head;

	if (*head && same_str((*head)->key, key_toremove))
	{
		temp = *head;
		*head = (*head)->next;
		free_node(temp);
		return ;
	}
	moving_head = *head;
	while (moving_head && moving_head->next)
	{
		if (same_str(moving_head->next->key, key_toremove))
		{
			temp = moving_head->next;
			moving_head->next = moving_head->next->next;
			free_node(temp);
		}
		moving_head = moving_head->next;
	}
}

void	remove_arg(t_node **node, char *arg)
{
	if (!node || !(*node))
		return ;
	remove_node(node, arg);
}

void	ft_unset(t_cmd *cmd)
{
	int		i;

	i = -1;
	if (!cmd->cmd_args)
		return ;
	while (cmd->cmd_args[++i])
	{
		remove_arg(&(cmd->env->node), cmd->cmd_args[i]);
		remove_arg(cmd->lvar, cmd->cmd_args[i]);
	}
	dict_env_to_arr(cmd->env);
	cmd->success_flg = 1;
}
