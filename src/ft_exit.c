/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:56:59 by iatopchu          #+#    #+#             */
/*   Updated: 2024/11/10 13:57:00 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	only_digits(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '+' && str[i] != '-')
			return (0);
	}
	return (1);
}

void	ft_exit(t_cmd *cmd)
{
	int	len;

	len = ft_arrlen(cmd->cmd_args);
	if (len > 1)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		cmd->exit_stat = 1;
		return ;
	}
	else if (len == 1)
	{
		if (!only_digits(cmd->cmd_args[0]))
		{
			ft_putendl_fd("exit: numeric argument required", 2);
			cmd->exit_stat = 2;
		}
		else
		{
			cmd->exit_stat = ft_atoi(cmd->cmd_args[0]);
			if (cmd->exit_stat > 255)
				cmd->exit_stat = cmd->exit_stat % 256;
		}
	}
	cmd->success_flg = 1;
	cmd->exit = 1;
}
