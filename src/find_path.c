/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:56:31 by iatopchu          #+#    #+#             */
/*   Updated: 2024/11/10 13:56:32 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	join_path(char **final_path, char *env_path, char *cmd)
{
	char	*temp;

	temp = ft_strjoin(env_path, "/");
	if (!temp)
		return ;
	*final_path = ft_strjoin(temp, cmd);
	if (!*final_path)
	{
		if (temp)
		{
			free(temp);
			temp = NULL;
		}
		return ;
	}
	if (temp)
	{
		free(temp);
		temp = NULL;
	}
}

int	construct_path(char **final_path, char **paths, char *cmd)
{
	int				i;
	struct dirent	*dir;
	DIR				*dir_stream;

	i = -1;
	while (paths[++i])
	{
		dir_stream = opendir(paths[i]);
		if (dir_stream)
		{
			dir = readdir(dir_stream);
			while (dir)
			{
				if (same_str(dir->d_name, cmd))
				{
					join_path(final_path, paths[i], cmd);
					closedir(dir_stream);
					return (1);
				}
				dir = readdir(dir_stream);
			}
			closedir(dir_stream);
		}
	}
	return (0);
}

void	find_path(t_cmd *cmd, char **final_path)
{
	char	*env_entry;
	char	**paths;
	int		i;

	env_entry = get_val(cmd->env->node, "PATH");
	if (!env_entry)
		return ;
	paths = ft_split(env_entry, ':');
	i = -1;
	if (!paths)
		return ;
	construct_path(final_path, paths, cmd->cmd_name);
	i = -1;
	while (paths && paths[++i])
	{
		free(paths[i]);
		paths[i] = NULL;
	}
	if (paths)
	{
		free(paths);
		paths = NULL;
	}
}
