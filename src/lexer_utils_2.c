/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:57:58 by iatopchu          #+#    #+#             */
/*   Updated: 2024/11/10 13:57:59 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "executor.h"

char	*ft_readline(char *prompt)
{
	char	*input;

	input = readline(prompt);
	if (input)
		add_history(input);
	return (input);
}

int	isquote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int	isquote_type(char *type)
{
	if (ft_strncmp(type, "FIELD", 10) == 0
		|| ft_strncmp(type, "EXP_FIELD", 10) == 0)
		return (1);
	return (0);
}

void	init_values(char **prev_type, int *i, int *num, int *len)
{
	*i = 0;
	*num = 0;
	*len = 0;
	*prev_type = NULL;
}

int	is_new_token_type(char *prev_type, char *cur_type)
{
	if (prev_type && ((ft_strncmp(cur_type, prev_type, 10) != 0)
			|| (ft_strncmp(prev_type, "FIELD", 10) == 0
				&& ft_strncmp(cur_type, "FIELD", 10) == 0)
			|| (ft_strncmp(prev_type, "EXP_FIELD", 10) == 0
				&& ft_strncmp(cur_type, "EXP_FIELD", 10) == 0)))
		return (1);
	return (0);
}
