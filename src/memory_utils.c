/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:17:16 by dbisko            #+#    #+#             */
/*   Updated: 2024/11/12 12:17:17 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_protect(char *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

int	ft_listlen(t_token *tokens_list)
{
	int	i;

	i = 0;
	while (tokens_list && tokens_list[i].type)
		i++;
	return (i);
}

void	free_lexer_data(t_token *tokens_list)
{
	int	i;
	int	len;

	i = 0;
	len = ft_listlen(tokens_list);
	if (tokens_list)
	{
		while (i < len)
		{
			if (tokens_list[i].begin)
			{
				free(tokens_list[i].begin);
				tokens_list[i].begin = NULL;
			}
			i++;
		}
		free(tokens_list);
		tokens_list = NULL;
	}
}

void	free_lexer_data_2(t_token *tokens_list, int len)
{
	int	i;

	i = 0;
	if (tokens_list)
	{
		while (i < len)
		{
			if (tokens_list[i].begin
				&& (same_str(tokens_list[i].type, "ENV_EXP")
					|| same_str(tokens_list[i].type, "EXP_FIELD")
					|| same_str(tokens_list[i].type, "FIELD")))
			{
				free(tokens_list[i].begin);
				tokens_list[i].begin = NULL;
			}
			i++;
		}
		free(tokens_list);
		tokens_list = NULL;
	}
}

char	**allocate_arr(char **envp)
{
	int		i;
	int		len;
	char	**env;

	i = -1;
	if (!envp || !(*envp))
		return (NULL);
	len = ft_arrlen(envp);
	env = (char **)malloc((len + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	while (envp[++i])
	{
		env[i] = ft_strdup(envp[i]);
	}
	env[i] = NULL;
	return (env);
}
