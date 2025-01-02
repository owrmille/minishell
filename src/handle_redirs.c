/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:57:38 by iatopchu          #+#    #+#             */
/*   Updated: 2024/11/10 13:57:39 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	process_heredoc(t_cmd *cmd, int len, int option)
{
	int		pipe_fd[2];
	t_info	*d;
	pid_t	pid;

	d = init_info(cmd, pipe_fd);
	if (!is_pipe_handled_successfully(cmd, d))
		return (0);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (0);
	}
	else if (pid == 0)
		handle_heredoc_in_child(cmd, d, len);
	else
		handle_heredoc_in_parent(cmd, d, option, pid);
	setup_parent_signals();
	return (1);
}

int	process_in(t_cmd *cmd, char *file, int *i)
{
	int		fd;

	if (access(file, F_OK) == -1 || access(file, R_OK) == -1)
	{
		cmd->exit_stat = 1;
		return (0);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		cmd->exit_stat = 1;
		return (0);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		cmd->exit_stat = 1;
		close (fd);
		return (0);
	}
	close (fd);
	(*i)++;
	return (1);
}

int	process_out(t_cmd *cmd, char *file, int *i)
{
	int		fd;

	if (access(file, F_OK) == 0 && access(file, W_OK) == -1)
	{
		cmd->exit_stat = 1;
		return (0);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		cmd->exit_stat = 1;
		return (0);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		cmd->exit_stat = 1;
		close (fd);
		return (0);
	}
	close (fd);
	(*i)++;
	return (1);
}

int	process_out_append(t_cmd *cmd, char *file, int *i)
{
	int		fd;

	if (access(file, F_OK) == 0 && access(file, W_OK) == -1)
	{
		cmd->exit_stat = 1;
		return (0);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		cmd->exit_stat = 1;
		return (0);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		cmd->exit_stat = 1;
		close (fd);
		return (0);
	}
	close (fd);
	(*i)++;
	return (1);
}

int	process_redirs(t_cmd *cmd)
{
	int		i;
	int		first_time;
	int		ok_flgs[2];

	first_time = 0;
	i = -1;
	ok_flgs[0] = 1;
	ok_flgs[1] = 1;
	while (cmd->redirects_arr && cmd->redirects_arr[++i])
	{
		if (same_str(cmd->redirects_arr[i], "RIN") && ok_flgs[1] == 1)
			ok_flgs[1] = process_in(cmd, cmd->redirects_arr[i + 1], &i);
		else if (same_str(cmd->redirects_arr[i], "ROUT") && ok_flgs[1] == 1)
			ok_flgs[1] = process_out(cmd, cmd->redirects_arr[i + 1], &i);
		else if (same_str(cmd->redirects_arr[i], "APPEND") && ok_flgs[1] == 1)
			ok_flgs[1] = process_out_append(cmd, cmd->redirects_arr[i + 1], &i);
		if (ok_flgs[1] == 0 && first_time == 0)
		{
			first_time = 1;
			ok_flgs[0] = 0;
			perror("redirection: ");
		}
	}
	return (ok_flgs[0]);
}
