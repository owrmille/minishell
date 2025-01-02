/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:58:31 by iatopchu          #+#    #+#             */
/*   Updated: 2024/11/10 13:58:32 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	check_file_type(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == -1)
		return (-1);
	if (S_ISREG(statbuf.st_mode))
		return (0);
	else if (S_ISDIR(statbuf.st_mode))
		return (1);
	else
		return (2);
}

int	is_regfile_or_dir(t_cmd *cmd, int type_num)
{
	if (type_num == 1)
	{
		cmd->exit_stat = 126;
		ft_putstr_fd(cmd->cmd_name, 2);
		ft_putendl_fd(": Is a directory", 2);
	}
	else if (type_num == 2)
	{
		cmd->exit_stat = 126;
		ft_putstr_fd(cmd->cmd_name, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	else
		return (0);
	return (1);
}

int	has_permissions_for_executable(t_cmd *cmd)
{
	if (access(cmd->cmd_name, F_OK) == -1)
	{
		perror("access");
		cmd->exit_stat = 127;
		return (0);
	}
	else if (access(cmd->cmd_name, X_OK) == -1)
	{
		perror("access");
		cmd->exit_stat = 126;
		return (0);
	}
	return (1);
}

void	follow_path_and_execute(t_cmd *cmd, char *final_path)
{
	if (final_path)
	{
		if (access(final_path, X_OK) == -1)
		{
			free_protect(final_path);
			perror("access");
			exit(126);
		}
		if (process_redirs(cmd))
		{
			if (execve(final_path, cmd->cmd_arr_w_name, cmd->env->arr) == -1)
			{
				free_protect(final_path);
				perror("execve");
				exit(126);
			}
		}
	}
	else
	{
		cmd->exit_stat = 127;
		ft_putstr_fd(cmd->cmd_name, 2);
		ft_putendl_fd(": command not found", 2);
	}
}

void	process_external(t_cmd *cmd)
{
	char	*final_path;
	int		type_num;

	setup_child_signals();
	final_path = NULL;
	if (cmd->cmd_name[0] == '/' || cmd->cmd_name[0] == '.')
	{
		type_num = check_file_type(cmd->cmd_name);
		if (is_regfile_or_dir(cmd, type_num))
			exit(cmd->exit_stat);
		else
		{
			if (!has_permissions_for_executable(cmd))
				exit(cmd->exit_stat);
			else
				final_path = cmd->cmd_name;
		}
	}
	else
		find_path(cmd, &final_path);
	follow_path_and_execute(cmd, final_path);
	free_protect(final_path);
}
