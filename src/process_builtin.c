/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:58:25 by iatopchu          #+#    #+#             */
/*   Updated: 2024/11/10 13:58:26 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	isbuiltin(t_cmd *cmd)
{
	int		i;
	char	*builtins[7];

	builtins[0] = "cd";
	builtins[1] = "echo";
	builtins[2] = "pwd";
	builtins[3] = "env";
	builtins[4] = "export";
	builtins[5] = "unset";
	builtins[6] = "exit";
	i = -1;
	while (++i < 7)
	{
		if (same_str(cmd->cmd_name, builtins[i]))
			return (1);
	}
	return (0);
}

void	execute_builtin(t_cmd *cmd)
{
	if (same_str(cmd->cmd_name, "echo"))
		ft_echo(cmd);
	else if (same_str(cmd->cmd_name, "pwd"))
		ft_pwd(cmd);
	else if (same_str(cmd->cmd_name, "env"))
		ft_env(cmd);
	else if (same_str(cmd->cmd_name, "cd"))
		ft_cd(cmd);
	else if (same_str(cmd->cmd_name, "export"))
		ft_export(cmd);
	else if (same_str(cmd->cmd_name, "unset"))
		ft_unset(cmd);
	else if (same_str(cmd->cmd_name, "exit"))
		ft_exit(cmd);
}

void	process_builtin(t_cmd *cmd)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
	{
		perror("dup");
		return ;
	}
	if (process_redirs(cmd))
		execute_builtin(cmd);
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		perror("failed to restore stdin");
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		perror("failed to restore stdout");
	close(saved_stdin);
	close(saved_stdout);
}
