/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:57:28 by iatopchu          #+#    #+#             */
/*   Updated: 2024/11/16 14:11:46 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	does_receive_delimeter(t_cmd *cmd, int i, char *line)
{
	if (!ft_strncmp(line, cmd->here_doc_delim[i],
			ft_strlen(cmd->here_doc_delim[i]))
		&& ft_strlen(line) == ft_strlen(cmd->here_doc_delim[i]) + 1
		&& line[ft_strlen(line) - 1] == '\n')
	{
		free_protect(line);
		return (1);
	}
	return (0);
}

void	print_heredoc_eof_message(char *delimeter)
{
	ft_putstr_fd("\nMinishell: warning: end-of-file wanted: ", 2);
	ft_putstr_fd(delimeter, 2);
	ft_putstr_fd("\n", 2);
}

void	write_heredoc_output(char *line, t_info *d, int len, int i)
{
	char	*temp;

	temp = insert_var(line, d, ft_strlen(line));
	if (len == 1 || i == len - 1)
		write(d->pipe_fd[1], temp, ft_strlen(temp));
	free_protect(line);
	free_protect(temp);
}

int	read_and_write_heredoc_content(t_cmd *cmd, t_info *d, int len)
{
	char	*line;
	int		i;

	i = -1;
	while (cmd->here_doc_delim[++i])
	{
		while (1)
		{
			write(STDOUT_FILENO, "> ", 2);
			line = get_next_line(STDIN_FILENO);
			if (!line && g_interrupted == 0)
			{
				print_heredoc_eof_message(cmd->here_doc_delim[i]);
				break ;
			}
			if (does_receive_delimeter(cmd, i, line))
				break ;
			if (cmd->cmd_name)
				write_heredoc_output(line, d, len, i);
		}
	}
	if (cmd->cmd_name)
		return (1);
	else
		return (0);
}

t_info	*init_info(t_cmd *cmd, int *pipe_fd)
{
	t_info	*d;

	d = (t_info *)malloc(sizeof(t_info));
	if (!d)
	{
		cmd->exit_stat = 1;
		return (NULL);
	}
	d->env = cmd->env->node;
	d->lv = *cmd->lvar;
	d->exit_status = 0;
	d->pipe_fd = pipe_fd;
	return (d);
}
