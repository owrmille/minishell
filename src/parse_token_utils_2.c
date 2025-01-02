/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:12:26 by dbisko            #+#    #+#             */
/*   Updated: 2024/11/12 12:12:56 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pipe(t_cmd **head, t_cmd **cmd, t_env *l_env, t_node **lvar)
{
	if (*cmd != NULL)
		add_command(head, *cmd);
	*cmd = create_command_node(l_env, lvar);
	return (1);
}

int	redir_validity(t_token *tkns, int i, int *err)
{
	int	index;

	index = i + 1;
	while (index < cnt_tkns(tkns) && ft_strcmp(tkns[index].type, "SEP") == 0)
		index++;
	if (index >= cnt_tkns(tkns)
		|| !(ft_strcmp(tkns[index].type, "WORD") == 0
			|| ft_strcmp(tkns[index].type, "FIELD") == 0
			|| ft_strcmp(tkns[index].type, "EXP_FIELD") == 0
			|| ft_strcmp(tkns[index].type, "ENV_EXP") == 0))
	{
		write(2, "Syntax error near unexpected token\n", 35);
		*err = 2;
		return (1);
	}
	return (0);
}

int	filename_len(t_token *tkns, int i)
{
	int	len;
	int	index;

	index = i;
	len = 0;
	while (index < cnt_tkns(tkns)
		&& (ft_strcmp(tkns[index].type, "WORD") == 0
			|| ft_strcmp(tkns[index].type, "FIELD") == 0
			|| ft_strcmp(tkns[index].type, "EXP_FIELD") == 0
			|| ft_strcmp(tkns[index].type, "ENV_EXP") == 0))
	{
		len += tkns[index].len;
		index++;
	}
	return (len);
}

char	*ft_strncat_len(char *dest, const char *src, int len)
{
	int	dest_len;
	int	i;

	dest_len = 0;
	i = 0;
	while (dest[dest_len] != '\0')
		dest_len++;
	while (i < len && src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}

void	concat_word(t_token *tkns, int *index, char **filename)
{
	int	len;

	len = filename_len(tkns, *index);
	*filename = (char *)malloc((len + 1) * sizeof(char));
	if (!*filename)
		return ;
	(*filename)[0] = '\0';
	while (*index < cnt_tkns(tkns)
		&& (ft_strcmp(tkns[*index].type, "WORD") == 0
			|| ft_strcmp(tkns[*index].type, "FIELD") == 0
			|| ft_strcmp(tkns[*index].type, "EXP_FIELD") == 0
			|| ft_strcmp(tkns[*index].type, "ENV_EXP") == 0))
	{
		ft_strncat_len(*filename, tkns[*index].begin, tkns[*index].len);
		(*index)++;
	}
}

// void	add_to_arr(char ***arr, char *str)
// {
// 	int	a_len;

// 	if (!*arr)
// 	{
// 		*arr = (char **)malloc(2 * sizeof(char *));
// 		if (!*arr)
// 			return ;
// 		(*arr)[0] = ft_strdup(str);
// 		(*arr)[1] = NULL;
// 	}
// 	else
// 	{
// 		a_len = arr_len(*arr);
// 		*arr = (char **)ft_realloc(*arr, (a_len + 1) * sizeof(char *),
// 				(a_len + 2) * sizeof(char *));
// 		if (!*arr)
// 			return ;
// 		(*arr)[a_len] = ft_strdup(str);
// 		(*arr)[a_len + 1] = NULL;
// 	}
// }

// int	place_name(t_cmd *cmd, char *arg, int w_idx, int i)
// {
// 	cmd->cmd_name = ft_substrdup(arg, ft_strlen(arg));
// 	free_protect(arg);
// 	return (w_idx - i);
// }
