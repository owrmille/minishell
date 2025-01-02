/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:19:18 by dbisko            #+#    #+#             */
/*   Updated: 2024/11/12 12:19:19 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hndl_signal_wait_children(t_cmd *cmd)
{
	if (WTERMSIG(cmd->exit_stat) == SIGQUIT)
	{
		write(1, "Quit (core dumped)\n", 19);
		cmd->exit_stat = 131;
	}
	else
	{
		cmd->exit_stat = 130;
		write(1, "\n", 1);
	}
}

void	wait_for_children(pid_t *child_pids, int child_count, t_cmd *cmd)
{
	int		i;
	pid_t	child_pid;

	i = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (i < child_count)
	{
		child_pid = waitpid(child_pids[i], &(cmd->exit_stat), 0);
		if (child_pid == -1)
		{
			perror("waitpid");
			break ;
		}
		if (WIFSIGNALED(cmd->exit_stat))
			hndl_signal_wait_children(cmd);
		else
			cmd->exit_stat = WEXITSTATUS(cmd->exit_stat);
		i++;
	}
	setup_parent_signals();
}

int	count_commands(t_cmd *cmd)
{
	int		count;
	t_cmd	*temp;

	count = 0;
	temp = cmd;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

void	handle_parent_process(t_cmd *cmd, t_cmd *temp)
{
	if (cmd->prev_fd != -1)
		close(cmd->prev_fd);
	if (temp->next != NULL)
		close(cmd->fd[1]);
	cmd->child_pids[cmd->index] = temp->pid;
	cmd->index++;
	cmd->prev_fd = cmd->fd[0];
	temp = temp->next;
}

void	heredoc_in_pipes(t_cmd *temp, int prev_fd)
{
	int	len;

	if (temp->here_doc_delim && prev_fd == -1)
	{
		len = 0;
		while (temp->here_doc_delim[len])
			len++;
		process_heredoc(temp, len, 2);
	}
}
