/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:18:51 by dbisko            #+#    #+#             */
/*   Updated: 2024/11/16 14:27:07 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_vals(t_node **env_node, t_node *lvars_node)
{
	t_node	*e_node;
	t_node	*l_node;

	e_node = *env_node;
	while (e_node)
	{
		l_node = lvars_node;
		while (l_node)
		{
			if (same_str(e_node->key, l_node->key)
				&& !same_str(e_node->val, l_node->val))
			{
				change_val(e_node, e_node->key, l_node->val);
			}
			l_node = l_node->next;
		}
		e_node = e_node->next;
	}
}

void	single_cmd_child(t_cmd *cmd)
{
	int	len;
	int	is_heredoc_interrupted;

	is_heredoc_interrupted = 0;
	setup_child_signals();
	if (cmd->here_doc_delim)
	{
		len = 0;
		while (cmd->here_doc_delim[len])
			len++;
		process_heredoc(cmd, len, 1);
		if (cmd->exit_stat == 130)
			is_heredoc_interrupted = 1;
	}
	if (cmd->cmd_name && !is_heredoc_interrupted)
		process_external(cmd);
	exit(cmd->exit_stat);
}

void	single_cmd_parent(t_cmd *cmd, pid_t pid)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &(cmd->exit_stat), 0);
	if (WIFSIGNALED(cmd->exit_stat))
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
	setup_parent_signals();
}

void	single_cmd_buildtins(t_cmd *cmd)
{
	int	len;

	if (cmd->here_doc_delim)
	{
		len = 0;
		while (cmd->here_doc_delim[len])
			len++;
		process_heredoc(cmd, len, 2);
	}
	process_builtin(cmd);
}

int	execute_single_command(t_cmd *cmd)
{
	pid_t	pid;

	if (cmd->cmd_name && isbuiltin(cmd))
		single_cmd_buildtins(cmd);
	else
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (-1);
		}
		else if (pid == 0)
			single_cmd_child(cmd);
		else
			single_cmd_parent(cmd, pid);
	}
	if (cmd->exit_stat == 127)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd->cmd_name, 2);
		return (-1);
	}
	return (0);
}
