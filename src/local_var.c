/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:16:39 by dbisko            #+#    #+#             */
/*   Updated: 2025/01/02 22:05:58 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_val(t_node *list, char *key, char *val)
{
	t_node	*temp;

	temp = list;
	while (temp && same_str(temp->key, key) != 1)
		temp = temp->next;
	if (!temp)
		return ;
	free_protect(temp->val);
	temp->val = ft_strdup(val);
}

void	add_node_lvar(t_cmd *cur_cmd, char *temp)
{
	char	*key;
	char	*val;

	key = key_def(temp);
	val = find_val(temp);
	if (key_exists(*cur_cmd->lvar, key) == 1)
		replace_val(*cur_cmd->lvar, key, val);
	else
		add_node(cur_cmd->lvar, key, val);
	free(key);
}

char	*create_token_copy(t_token *tkns, int i)
{
	char	*temp;

	temp = (char *)malloc(tkns[i].len + 1);
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, tkns[i].begin, tkns[i].len + 1);
	temp[tkns[i].len] = '\0';
	return (temp);
}

char	*concatenate_tokens(t_token *tkns, int *i, int *w_idx, char *temp)
{
	int		current_len;
	char	*new_temp;

	while ((*i + *w_idx + 1) < cnt_tkns(tkns)
		&& is_appdbl(tkns, *w_idx + *i) == 1)
	{
		current_len = tkns[*i + *w_idx].len;
		new_temp = ft_realloc(temp, ft_strlen(temp),
				ft_strlen(temp) + current_len + 1);
		if (!new_temp)
		{
			free(temp);
			return (NULL);
		}
		temp = new_temp;
		ft_strncat(temp, tkns[*i + *w_idx + 1].begin,
			tkns[*i + *w_idx + 1].len);
		(*w_idx)++;
	}
	return (temp);
}

int	add_lvar(t_token *tkns, t_cmd *cur_cmd, int i)
{
	int		w_idx;
	char	*temp;

	w_idx = 0;
	temp = create_token_copy(tkns, i);
	if (!temp)
		return (-1);
	temp = concatenate_tokens(tkns, &i, &w_idx, temp);
	if (!temp)
		return (-1);
	add_node_lvar(cur_cmd, temp);
	free(temp);
	return (w_idx);
}
