/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:56:50 by iatopchu          #+#    #+#             */
/*   Updated: 2024/11/10 13:56:51 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	ft_arrlen(char **arr)
{
	int	len;

	len = 0;
	while (arr && arr[len])
		len++;
	return (len);
}

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	flg;

	i = 0;
	flg = 0;
	if (cmd->cmd_args)
	{
		if (same_str(cmd->cmd_args[0], "-n"))
		{
			i++;
			flg = 1;
		}
		while (i < ft_arrlen(cmd->cmd_args))
		{
			ft_putstr_fd(cmd->cmd_args[i++], 1);
			if (i != ft_arrlen(cmd->cmd_args))
				ft_putchar_fd(' ', 1);
		}
	}
	if (flg == 0)
		write(1, "\n", 1);
	cmd->success_flg = 1;
}
