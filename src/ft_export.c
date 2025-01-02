/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:57:11 by iatopchu          #+#    #+#             */
/*   Updated: 2024/11/10 13:57:12 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	process_pair(char *arg, t_cmd *cmd)
{
	char	*key;
	char	*val;

	split_key_value(arg, &key, &val);
	if (!key || !val)
		perror((const char *)key);
	else if (!valid_key(key))
	{
		ft_putstr_fd(key, 2);
		ft_putendl_fd(": not a valid identifier", 2);
		cmd->exit_stat = 1;
	}
	else
	{
		if (!add_or_update_env(&cmd->env->node, key, val, cmd))
			cmd->exit_stat = 1;
	}
	free_protect(key);
	free_protect(val);
	return (1);
}

int	process_key(char *arg, t_cmd *cmd)
{
	char	*key;
	char	*val;
	t_node	*lvar;

	lvar = *cmd->lvar;
	key = arg;
	val = get_val(lvar, key);
	if (!(*key))
		perror((const char *)key);
	else if (!valid_key(key))
	{
		ft_putstr_fd(key, 2);
		ft_putendl_fd(": not a valid identifier", 2);
		cmd->exit_stat = 1;
	}
	else if (!val)
		return (1);
	else
	{
		if (!add_or_update_env(&cmd->env->node, key, val, cmd))
			cmd->exit_stat = 1;
	}
	return (1);
}

int	has_pair(char *arg)
{
	if (char_in_str('=', arg, ft_strlen(arg)) && ft_strlen(arg) >= 3)
		return (1);
	return (0);
}

int	has_only_key(char *arg)
{
	if (arg && !char_in_str('=', arg, ft_strlen(arg)))
		return (1);
	return (0);
}

void	ft_export(t_cmd *cmd)
{
	int	i;

	i = -1;
	if (!cmd->cmd_args)
		ft_env(cmd);
	else
	{
		while (cmd->cmd_args[++i])
		{
			if (has_pair(cmd->cmd_args[i]))
			{
				process_pair(cmd->cmd_args[i], cmd);
			}
			else if (has_only_key(cmd->cmd_args[i]))
				process_key(cmd->cmd_args[i], cmd);
			else
			{
				ft_putstr_fd(cmd->cmd_args[i], 2);
				ft_putendl_fd(": not a valid identifier", 2);
				cmd->exit_stat = 1;
			}
		}
		dict_env_to_arr(cmd->env);
	}
	cmd->success_flg = 1;
}
