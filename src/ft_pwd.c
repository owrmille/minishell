/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:57:16 by iatopchu          #+#    #+#             */
/*   Updated: 2024/11/10 13:57:17 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	ft_pwd(t_cmd *cmd)
{
	char	buf[PATH_MAX];

	if (!getcwd(buf, PATH_MAX))
		ft_putendl_fd("pwd: error retrieving current directory", 2);
	else
	{
		ft_putendl_fd(buf, 1);
		cmd->success_flg = 1;
	}
}
