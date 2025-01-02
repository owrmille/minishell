/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:56:23 by iatopchu          #+#    #+#             */
/*   Updated: 2024/11/16 14:34:40 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_squotes(char *str, int *i, t_token *tokens, int *token_num)
{
	char	*tmp;
	int		j;
	int		close_flg;

	close_flg = 0;
	j = *i;
	while (str[++(*i)])
	{
		if (str[*i] == '\'')
		{
			close_flg = 1;
			break ;
		}
	}
	if (close_flg == 0)
		return ;
	tmp = ft_substr(str, j + 1, *i - j - 1);
	tokens[*token_num].len = *i - j - 1;
	free_protect(tokens[*token_num].begin);
	tokens[*token_num].begin = tmp;
}

int	iskey(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

char	*ft_dollar(char *str, int *i)
{
	char	*key;
	int		j;

	j = *i;
	while (str[++(*i)])
	{
		if (!iskey(str[*i]))
			break ;
	}
	key = ft_substr(str, j + 1, *i - j - 1);
	return (key);
}

void	ft_dquotes(char *str, int *i, t_token *tokens, int *token_num)
{
	char	*tmp;
	int		j;
	int		close_flg;

	close_flg = 0;
	j = *i;
	while (str[++(*i)])
	{
		if (str[*i] == '\"')
		{
			close_flg = 1;
			break ;
		}
	}
	if (close_flg == 0)
		return ;
	tmp = ft_substr(str, j + 1, *i - j - 1);
	tokens[*token_num].len = *i - j - 1;
	free_protect(tokens[*token_num].begin);
	tokens[*token_num].begin = tmp;
}

void	expander(char *input, int *i, t_token *tokens, int *token_num)
{
	if (isquote(input[*i]))
	{
		if (input[*i] == '\'')
		{
			ft_squotes(input, i, tokens, token_num);
		}
		else if (input[*i] == '"')
		{
			ft_dquotes(input, i, tokens, token_num);
		}
	}
}
