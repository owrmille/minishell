/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:19:02 by dbisko            #+#    #+#             */
/*   Updated: 2024/11/16 14:31:48 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_pipe(int *fd)
{
	if (pipe(fd) == -1)
		return (-1);
	return (1);
}

void	handle_input_redirection(int prev_fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
}

void	handle_output_redirection(t_cmd *temp, int *fd)
{
	if (temp->next != NULL)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
}

void	heredoc_in_fork(t_cmd *temp)
{
	if (temp->heredoc_fd != -1)
	{
		if (dup2(temp->heredoc_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 heredoc_fd");
			exit(1);
		}
		close(temp->heredoc_fd);
	}
}

void	fork_and_execute(t_cmd *temp, int prev_fd, int *fd)
{
	if (temp->here_doc_delim)
		heredoc_in_fork(temp);
	else
		handle_input_redirection(prev_fd);
	handle_output_redirection(temp, fd);
	if (isbuiltin(temp))
	{
		if (ft_strcmp(temp->cmd_name, "cd") == 0
			|| ft_strcmp(temp->cmd_name, "exit") == 0)
			exit(temp->exit_stat);
		process_builtin(temp);
		exit(temp->exit_stat);
	}
	else
	{
		process_external(temp);
		if (!temp->success_flg && temp->exit_stat == 127)
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putendl_fd(temp->cmd_name, 2);
		}
		exit(temp->exit_stat);
	}
}
