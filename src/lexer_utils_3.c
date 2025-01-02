/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:58:01 by iatopchu          #+#    #+#             */
/*   Updated: 2024/11/10 13:58:02 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "executor.h"

void	iterate_vars(char **prev, char **cur, int *len, int *i)
{
	(*len)++;
	*prev = *cur;
	(*i) += add_extra(*prev);
	(*i)++;
}

void	last_token(t_token **tokens, char *prev, int len, char *str)
{
	int	num;

	num = ft_listlen(*tokens);
	(*tokens)[num].type = prev;
	if (!isquote_type(prev))
	{
		(*tokens)[num].len = len;
		(*tokens)[num].begin = str;
	}
}

void	update_num_len(int *num, int *len)
{
	(*num)++;
	*len = 0;
}

int	skip_symbol(char *cur_type)
{
	if (ft_strncmp(cur_type, "APPEND", 10) == 0
		|| ft_strncmp(cur_type, "INSOURCE", 10) == 0)
	{
		return (2);
	}
	return (1);
}

int	add_extra(char *type)
{
	if (ft_strncmp(type, "APPEND", 10) == 0
		|| ft_strncmp(type, "INSOURCE", 10) == 0)
	{
		return (1);
	}
	return (0);
}
