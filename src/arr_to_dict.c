/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_to_dict.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:55:34 by iatopchu          #+#    #+#             */
/*   Updated: 2024/11/10 13:55:35 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

t_node	*create_node(char *key, char *val)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->val = ft_strdup(val);
	if (!node->key || !node->val)
	{
		free_node(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

void	add_node(t_node **head, char *key, char *val)
{
	t_node	*node;
	t_node	*temp;

	temp = NULL;
	node = create_node(key, val);
	if (!node)
		return ;
	if (*head == NULL)
		*head = node;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = node;
	}
}

void	split_key_value(char *str, char **key, char **val)
{
	char	*equal_sign;
	char	*temp;

	temp = ft_strdup(str);
	equal_sign = ft_strchr(temp, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		*key = ft_strdup(temp);
		*val = ft_strdup(equal_sign + 1);
	}
	else
	{
		*key = ft_strdup(temp);
		*val = NULL;
	}
	free_protect(temp);
}

t_node	*arr_to_dict(char **env)
{
	t_node		*env_list;
	char		*key;
	char		*value;
	int			i;

	i = 0;
	env_list = NULL;
	while (env[i])
	{
		split_key_value(env[i], &key, &value);
		add_node(&env_list, key, value);
		free_protect(key);
		free_protect(value);
		i++;
	}
	return (env_list);
}
