/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:56:44 by iatopchu          #+#    #+#             */
/*   Updated: 2024/11/10 13:56:45 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*get_old_path(t_cmd *cmd, char *buf)
{
	char	*old_path;

	old_path = getcwd(buf, PATH_MAX);
	if (!old_path)
	{
		cmd->exit_stat = 1;
		ft_putendl_fd("cd: error retrieving current directory", 1);
		return (NULL);
	}
	return (old_path);
}

char	*determine_new_path(t_cmd *cmd)
{
	char	*new_path;
	char	*home_path;

	if (!cmd->cmd_args || !cmd->cmd_args[0])
		return (get_val(cmd->env->node, "HOME"));
	else
	{
		new_path = cmd->cmd_args[0];
		if (new_path[0] == '~')
		{
			home_path = get_val(cmd->env->node, "HOME");
			if (home_path)
				return (ft_strjoin(home_path, new_path + 1));
			else
			{
				cmd->exit_stat = 1;
				ft_putendl_fd("cd: HOME not set", 2);
				return (NULL);
			}
		}
	}
	return (new_path);
}

int	change_directory(t_cmd *cmd, char *new_path)
{
	if (chdir(new_path) == -1)
	{
		cmd->exit_stat = 1;
		ft_putendl_fd("cd: No such file or directory", 2);
		return (0);
	}
	return (1);
}

void	update_environment_paths(t_cmd *cmd, char *old_path, char *new_path_buf)
{
	if (getcwd(new_path_buf, PATH_MAX) == NULL)
	{
		cmd->exit_stat = 1;
		ft_putendl_fd("cd: error retrieving new directory", 2);
		return ;
	}
	change_val(cmd->env->node, "OLDPWD", old_path);
	change_val(cmd->env->node, "PWD", new_path_buf);
	cmd->success_flg = 1;
}

void	ft_cd(t_cmd *cmd)
{
	char	buf[PATH_MAX];
	char	buf2[PATH_MAX];
	char	*old_path;
	char	*new_path;

	if (are_too_many_arguments(cmd))
		return ;
	old_path = get_old_path(cmd, buf);
	if (!old_path)
		return ;
	new_path = determine_new_path(cmd);
	if (!new_path)
		return ;
	if (!change_directory(cmd, new_path))
		return ;
	update_environment_paths(cmd, old_path, buf2);
}
