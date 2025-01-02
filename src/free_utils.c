/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:17:03 by dbisko            #+#    #+#             */
/*   Updated: 2024/11/12 12:17:04 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_node *node)
{
	if (node)
	{
		if (node->key)
		{
			free(node->key);
			node->key = NULL;
		}
		if (node->val)
		{
			free(node->val);
			node->val = NULL;
		}
		free(node);
		node = NULL;
	}
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free_protect(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_list(t_node *node)
{
	t_node	*current_to_free;
	t_node	*next_to_free;

	current_to_free = node;
	while (current_to_free != NULL)
	{
		next_to_free = current_to_free->next;
		free_node(current_to_free);
		current_to_free = next_to_free;
	}
}

void	free_env(t_env *env)
{
	if (env)
	{
		free_list(env->node);
		free_arr(env->arr);
		free(env);
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*current_to_free;
	t_cmd	*next_to_free;

	current_to_free = cmd;
	while (current_to_free != NULL)
	{
		next_to_free = current_to_free->next;
		free_protect(current_to_free->cmd_name);
		free_arr(current_to_free->cmd_args);
		free_arr(current_to_free->cmd_arr_w_name);
		free_arr(current_to_free->here_doc_delim);
		free_arr(current_to_free->redirects_arr);
		free(current_to_free);
		current_to_free = NULL;
		current_to_free = next_to_free;
	}
}
