/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:56:16 by iatopchu          #+#    #+#             */
/*   Updated: 2024/11/10 13:56:17 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*insert_var(char *s, t_info *d, int token_len)
{
	int		i;
	int		end_key;
	char	*new_s;

	i = -1;
	end_key = -1;
	new_s = ft_strdup("");
	if (!new_s)
		return (NULL);
	while (s[++i] && i < token_len)
	{
		if (s[i] == '$' && s[i + 1] && (iskey(s[i + 1]) || s[i + 1] == '?'))
		{
			new_s = append_filling(new_s, s, end_key, i);
			end_key = put_val(&new_s, s, d, i + 1);
			if (end_key == -1)
				end_key = i;
			else if (end_key == -2)
				return (free_protect(new_s), NULL);
			i = end_key;
		}
	}
	if (end_key != i - 1)
		new_s = append_filling(new_s, s, end_key, i);
	return (new_s);
}

int	char_in_str(char c, char *str, int len)
{
	int	i;
	int	cnt;

	i = -1;
	cnt = 0;
	while (str[++i] && len-- > 0)
	{
		if (str[i] == c)
			cnt++;
	}
	return (cnt);
}

void	process_dollar_quotes(t_token *tokens, t_info *d, int i)
{
	char	*temp;
	char	*old_type;

	temp = insert_var(tokens[i].begin, d, tokens[i].len);
	old_type = tokens[i].type;
	tokens[i].type = "ENV_EXP";
	if (temp)
		tokens[i].len = ft_strlen(temp);
	else
		tokens[i].len = 0;
	if (tokens[i].len == 0)
	{
		free_protect(temp);
		tokens[i].begin = NULL;
	}
	else
	{
		if (old_type && same_str(old_type, "EXP_FIELD"))
			free_protect(tokens[i].begin);
		tokens[i].begin = temp;
	}
}

void	dollar_expander(t_token *tokens, t_node *env, t_node *l_var, int exit)
{
	int		i;
	int		len;
	t_info	*d;

	len = cnt_tkns(tokens);
	d = (t_info *)malloc(sizeof(t_info));
	d->env = env;
	d->lv = l_var;
	d->exit_status = exit;
	i = -1;
	while (++i < len)
	{
		if ((same_str(tokens[i].type, "EXP_FIELD")
				|| same_str(tokens[i].type, "WORD"))
			&& char_in_str('$', tokens[i].begin, tokens[i].len) > 0)
			process_dollar_quotes(tokens, d, i);
	}
	free(d);
}
