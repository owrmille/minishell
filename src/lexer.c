/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:58:11 by iatopchu          #+#    #+#             */
/*   Updated: 2024/11/10 13:58:12 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	store_tokens(char *input, t_token *tokens)
{
	int		i;
	int		num;
	int		len;
	char	*cur_type;
	char	*prev_type;

	init_values(&prev_type, &i, &num, &len);
	while (input[i])
	{
		cur_type = define_token_type(input, i);
		if (is_new_token_type(prev_type, cur_type))
		{
			tokens[num].type = prev_type;
			if (!isquote_type(prev_type))
			{
				tokens[num].len = len + add_extra(prev_type);
				tokens[num].begin = input + i - len - add_extra(prev_type);
			}
			update_num_len(&num, &len);
		}
		expander(input, &i, tokens, &num);
		iterate_vars(&prev_type, &cur_type, &len, &i);
	}
	last_token(&tokens, prev_type, len, input + i - len);
}

void	copy_token_data(t_token *src, t_token **dest, int i, int *j)
{
	if (!(same_str(src[i].type, "SEP") && i == 0))
	{
		if (same_str(src[i].type, "ENV_EXP") && src[i].len > 0)
		{
			(*dest)[*j].begin = ft_strdup(src[i].begin);
			(*dest)[*j].type = src[i].type;
			(*dest)[*j].len = src[i].len;
			(*j)++;
		}
		else if (!same_str(src[i].type, "ENV_EXP") && src[i].len > 0)
		{
			(*dest)[*j].begin = ft_strdup(src[i].begin);
			(*dest)[*j].type = src[i].type;
			(*dest)[*j].len = src[i].len;
			(*j)++;
		}
	}
}

t_token	*remove_null_vals(t_token *src)
{
	t_token	*dest;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (src[j].type)
	{
		if (src[j].begin && !(same_str(src[j].type, "SEP") && j == 0))
			i++;
		j++;
	}
	dest = (t_token *)malloc(sizeof(t_token) * (i + 1));
	if (!dest)
		return (NULL);
	init_tokens_struct(&dest, i);
	i = -1;
	j = 0;
	while (src[++i].type)
		copy_token_data(src, &dest, i, &j);
	dest[j].type = NULL;
	dest[j].begin = NULL;
	dest[j].len = 0;
	return (dest);
}

void	init_tokens_struct(t_token **tokens, int tokens_num)
{
	int	i;

	i = 0;
	while (i <= tokens_num)
	{
		(*tokens)[i].type = NULL;
		(*tokens)[i].begin = NULL;
		(*tokens)[i].len = 0;
		i++;
	}
}

t_token	*lexer(char *input, t_env *env, t_node *l_vars, int exit_status)
{
	int		tokens_num;
	t_token	*tokens;
	t_token	*final_tokens;

	tokens_num = find_tokens_num(input);
	tokens = malloc((tokens_num + 1) * sizeof(t_token));
	if (!tokens)
		return (NULL);
	init_tokens_struct(&tokens, tokens_num);
	store_tokens(input, tokens);
	dollar_expander(tokens, env->node, l_vars, exit_status);
	final_tokens = remove_null_vals(tokens);
	free_lexer_data_2(tokens, tokens_num);
	return (final_tokens);
}
