/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:57:32 by iatopchu          #+#    #+#             */
/*   Updated: 2024/11/16 14:27:40 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	replace_heredoc_fd(t_cmd *cmd, int option, t_info *d)
{
	if (option == 2)
		cmd->heredoc_fd = d->pipe_fd[0];
	else if (option == 1)
	{
		if (dup2(d->pipe_fd[0], STDIN_FILENO) == -1)
		{
			cmd->exit_stat = 1;
			perror("dup2");
			close(d->pipe_fd[0]);
			if (d)
				free(d);
			return (0);
		}
		close(d->pipe_fd[0]);
	}
	return (1);
}

int	is_pipe_handled_successfully(t_cmd *cmd, t_info *d)
{
	if (pipe(d->pipe_fd) == -1)
	{
		cmd->exit_stat = 1;
		free(d);
		perror("pipe");
		return (0);
	}
	return (1);
}

void	handle_heredoc_in_child(t_cmd *cmd, t_info *d, int len)
{
	setup_heredoc_signals();
	close(d->pipe_fd[0]);
	read_and_write_heredoc_content(cmd, d, len);
	close(d->pipe_fd[1]);
	if (d)
		free(d);
	exit(cmd->exit_stat);
}

void	handle_heredoc_in_parent(t_cmd *cmd, t_info *d, int option, int pid)
{
	pid_t	child_pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	close(d->pipe_fd[1]);
	if (!replace_heredoc_fd(cmd, option, d))
		perror("replace heredoc pid");
	child_pid = waitpid(pid, &(cmd->exit_stat), 0);
	if (child_pid == -1)
		perror("waitpid");
	if (WIFSIGNALED(cmd->exit_stat))
	{
		if (WTERMSIG(cmd->exit_stat) == SIGINT)
		{
			cmd->exit_stat = 130;
			write(1, "\n", 1);
		}
	}
	else
		cmd->exit_stat = WEXITSTATUS(cmd->exit_stat);
	if (d)
		free(d);
	setup_parent_signals();
}
