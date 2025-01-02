/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:13:40 by dbisko            #+#    #+#             */
/*   Updated: 2024/11/12 12:13:43 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_command_node(t_env *env_data, t_node **lvar)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->cmd_name = NULL;
	node->cmd_args = NULL;
	node->cmd_arr_w_name = NULL;
	node->here_doc_delim = NULL;
	node->redirects_arr = NULL;
	node->env = env_data;
	node->lvar = lvar;
	node->next = NULL;
	node->success_flg = 0;
	node->exit = 0;
	node->exit_stat = 0;
	node->heredoc_fd = 0;
	return (node);
}

char	**dup_args(char **concat_args, char **args, int arr_len)
{
	int	i;

	i = 0;
	while (i < arr_len)
	{
		concat_args[i + 1] = ft_strdup(args[i]);
		if (concat_args[i + 1] == NULL)
		{
			while (i >= 0)
			{
				free(concat_args[i]);
				i--;
			}
			free(concat_args);
			return (NULL);
		}
		i++;
	}
	return (concat_args);
}

int	set_arr_len(char **args)
{
	int	len;

	if (args == NULL)
		len = 0;
	else
		len = ft_arrlen(args);
	return (len);
}

//concatenate name of the program with the list of args
char	**concat_name_args(char *name, char **args)
{
	char	**concat_args;
	int		arr_len;

	if (name == NULL && args == NULL)
		return (NULL);
	arr_len = set_arr_len(args);
	concat_args = (char **)malloc((arr_len + 2) * sizeof(char *));
	if (concat_args == NULL)
		return (NULL);
	concat_args[0] = ft_strdup(name);
	if (concat_args[0] == NULL)
	{
		free(concat_args);
		return (NULL);
	}
	if (dup_args(concat_args, args, arr_len) == NULL)
	{
		free(concat_args[0]);
		free(concat_args);
		return (NULL);
	}
	concat_args[arr_len + 1] = NULL;
	return (concat_args);
}

// adding command node to the end of the linked list
void	add_command(t_cmd **head, t_cmd *node)
{
	t_cmd	*temp;

	node->cmd_arr_w_name = concat_name_args(node->cmd_name, node->cmd_args);
	if (*head == NULL)
		*head = node;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = node;
	}
}
