/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unfinished_input.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:57:50 by iatopchu          #+#    #+#             */
/*   Updated: 2024/11/10 13:57:51 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_pipe_with_trailing_seps(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] == '|')
			return (1);
		else if (!ft_isspace(str[i]))
			return (0);
		i--;
	}
	return (0);
}

char	*process_option(char *complete_cmd, char *cutted_line, char option)
{
	char	*temp;
	char	*res;

	res = NULL;
	if (option == 'q')
	{
		temp = ft_strjoin(complete_cmd, "\n");
		res = ft_strjoin(temp, cutted_line);
		free_protect(temp);
	}
	else if (option == 'p')
		res = ft_strjoin(complete_cmd, cutted_line);
	return (res);
}

char	*concat_command(char *complete_cmd, char *line, char option)
{
	char	*res;
	char	*cutted_line;

	cutted_line = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!cutted_line)
	{
		free_protect(line);
		return (NULL);
	}
	ft_strlcpy(cutted_line, line, ft_strlen(line));
	res = process_option(complete_cmd, cutted_line, option);
	free_protect(line);
	free_protect(cutted_line);
	free_protect(complete_cmd);
	if (!res)
		return (NULL);
	return (res);
}

char	*read_complete_cmd(char *complete_cmd, char option, char *prompt)
{
	char	*line;
	char	*res;

	while (1)
	{
		ft_putstr_fd(prompt, 1);
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (line)
		{
			res = concat_command(complete_cmd, line, option);
			if ((option == 'p' && !has_pipe_with_trailing_seps(res))
				|| (option == 'q' && !has_unclosed_quotes(res)))
				break ;
			complete_cmd = res;
		}
	}
	return (res);
}

char	*handle_unfinished_input(char *input)
{
	char	*complete_cmd;

	complete_cmd = input;
	if (has_unclosed_quotes(input))
		complete_cmd = read_complete_cmd(complete_cmd, 'q', "dquote");
	else if (has_pipe_with_trailing_seps(input))
		complete_cmd = read_complete_cmd(complete_cmd, 'p', "pipe");
	if (!complete_cmd)
		return (input);
	return (complete_cmd);
}
