/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:56:55 by iatopchu          #+#    #+#             */
/*   Updated: 2024/11/10 13:56:56 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	ft_env(t_cmd *cmd)
{
	t_env	temp;

	temp = *cmd->env;
	if (cmd->cmd_args)
	{
		cmd->exit_stat = 2;
		ft_putendl_fd("env: too many arguments", 2);
	}
	if (!cmd->env->arr)
	{
		cmd->exit = 2;
		ft_putendl_fd("env: error retrieving environment variables", 2);
	}
	if (!cmd->cmd_args && cmd->env->node)
	{
		cmd->success_flg = 1;
		while (cmd->env->node)
		{
			ft_putstr_fd(cmd->env->node->key, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(cmd->env->node->val, 1);
			cmd->env->node = cmd->env->node->next;
		}
	}
	*(cmd->env) = temp;
}
