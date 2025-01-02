/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_utils_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:11:58 by dbisko            #+#    #+#             */
/*   Updated: 2024/11/12 12:12:04 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_arr(char ***arr, char *str)
{
	int	a_len;

	if (!*arr)
	{
		*arr = (char **)malloc(2 * sizeof(char *));
		if (!*arr)
			return ;
		(*arr)[0] = ft_strdup(str);
		(*arr)[1] = NULL;
	}
	else
	{
		a_len = arr_len(*arr);
		*arr = (char **)ft_realloc(*arr, (a_len + 1) * sizeof(char *),
				(a_len + 2) * sizeof(char *));
		if (!*arr)
			return ;
		(*arr)[a_len] = ft_strdup(str);
		(*arr)[a_len + 1] = NULL;
	}
}

int	place_name(t_cmd *cmd, char *arg, int w_idx, int i)
{
	cmd->cmd_name = ft_substrdup(arg, ft_strlen(arg));
	free_protect(arg);
	return (w_idx - i);
}
