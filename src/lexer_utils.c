/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:58:07 by iatopchu          #+#    #+#             */
/*   Updated: 2024/11/10 13:58:08 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ft_isspace(char c)
{
	return (c == ' '
		|| c == '\n'
		|| c == '\t'
		|| c == '\r'
		|| c == '\v'
		|| c == '\f');
}

char	*define_token_type(char *input, int i)
{
	if (ft_isspace(input[i]))
		return ("SEP");
	else if (input[i] == '\'')
		return ("FIELD");
	else if (input[i] == '"')
		return ("EXP_FIELD");
	else if (input[i] == '>' && input[i + 1] == '>')
		return ("APPEND");
	else if (input[i] == '<' && input[i + 1] == '<')
		return ("INSOURCE");
	else if (input[i] == '>' && input[i + 1] != '>')
		return ("ROUT");
	else if (input[i] == '<' && input[i + 1] != '<')
		return ("RIN");
	else if (input[i] == '|')
		return ("PIPE");
	else
		return ("WORD");
}

void	process_quotes(char *input, int *i, int *tokens_num)
{
	(void)tokens_num;
	if (input[(*i)] == '\'')
	{
		while (input[++(*i)])
		{
			if (input[*i] == '\'')
			{
				break ;
			}
		}
	}
	else if (input[(*i)] == '"')
	{
		while (input[++(*i)])
		{
			if (input[*i] == '"')
			{
				break ;
			}
		}
	}
}

int	are_prev_cur_fields(char *prev_type, char *cur_type)
{
	if (prev_type && ((ft_strncmp(prev_type, "FIELD", 10) == 0
				&& ft_strncmp(cur_type, "FIELD", 10) == 0)
			|| (ft_strncmp(prev_type, "EXP_FIELD", 10) == 0
				&& ft_strncmp(cur_type, "EXP_FIELD", 10) == 0)))
		return (1);
	return (0);
}

int	find_tokens_num(char *input)
{
	int		i;
	int		tokens_num;
	char	*cur_type;
	char	*prev_type;

	i = 0;
	tokens_num = 0;
	prev_type = NULL;
	while (input[i])
	{
		cur_type = define_token_type(input, i);
		if ((prev_type && ft_strncmp(cur_type, prev_type, 10)) != 0)
			tokens_num++;
		if (are_prev_cur_fields(prev_type, cur_type))
			tokens_num++;
		if (isquote(input[i]))
		{
			prev_type = define_token_type(input, i);
			process_quotes(input, &i, &tokens_num);
		}
		prev_type = cur_type;
		i += skip_symbol(cur_type);
	}
	tokens_num++;
	return (tokens_num);
}
