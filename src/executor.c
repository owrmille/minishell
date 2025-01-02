/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:18:02 by dbisko            #+#    #+#             */
/*   Updated: 2024/11/12 12:18:03 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_error(pid_t *child_pids)
{
	perror("pipe error");
	free(child_pids);
	return (-1);
}

void	cmd_w_pipes_child(t_cmd *temp, int prev_fd, t_cmd *cmd)
{
	int	len;

	setup_child_signals();
	if (temp->here_doc_delim && prev_fd != -1 && cmd->cmd_name)
	{
		len = 0;
		while (temp->here_doc_delim[len])
			len++;
		process_heredoc(temp, len, 2);
	}
	fork_and_execute(temp, prev_fd, cmd->fd);
}

int	setup_env_pipes(t_cmd *cmd, t_cmd *temp)
{
	cmd->child_pids = malloc(sizeof(pid_t) * count_commands(cmd));
	if (!cmd->child_pids)
		return (child_pid_malloc_check());
	cmd->prev_fd = -1;
	cmd->index = 0;
	heredoc_in_pipes(temp, cmd->prev_fd);
	return (0);
}

int	execute_command_with_pipes(t_cmd *cmd)
{
	t_cmd	*temp;

	temp = cmd;
	if (setup_env_pipes(cmd, temp) != 0)
		return (-1);
	while (temp)
	{
		if (temp->next != NULL && pipe(cmd->fd) == -1)
			return (pipe_error(cmd->child_pids));
		temp->pid = fork();
		if (temp->pid == -1)
			return (pipe_error(cmd->child_pids));
		else if (temp->pid == 0)
		{
			cmd_w_pipes_child(temp, cmd->prev_fd, cmd);
		}
		else
		{
			handle_parent_process(cmd, temp);
			temp = temp->next;
		}
	}
	wait_for_children(cmd->child_pids, count_commands(cmd), cmd);
	free(cmd->child_pids);
	return (0);
}

int	executor(t_cmd *cmd)
{
	int	return_value;

	return_value = 0;
	if (cmd->next == NULL)
		return_value = execute_single_command(cmd);
	else
		return_value = execute_command_with_pipes(cmd);
	if (cmd->exit_stat > 255)
		cmd->exit_stat = cmd->exit_stat / 256;
	dict_env_to_arr(cmd->env);
	return (return_value);
}
