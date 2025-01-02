/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:15:25 by dbisko            #+#    #+#             */
/*   Updated: 2024/11/12 12:15:27 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_arg(t_token *tkns, t_cmd *cmd, int i)
{
	int		w_idx;
	char	*arg;

	w_idx = i;
	arg = NULL;
	concat_word(tkns, &w_idx, &arg);
	if (!arg)
		return (0);
	if (cmd->cmd_name == NULL)
	{
		if (var_found(tkns[i].begin, tkns[i].len))
		{
			add_node_lvar(cmd, arg);
			free_protect(arg);
			return (w_idx - i);
		}
		else
			return (place_name(cmd, arg, w_idx, i));
	}
	else
	{
		add_to_arr(&cmd->cmd_args, arg);
		free_protect(arg);
		return (w_idx - i);
	}
}

int	hndl_rin(t_token *tkns, t_cmd *cmd, int i, int *err)
{
	int		w_idx;
	char	*filename;

	if (redir_validity(tkns, i, err) == 1)
		return (0);
	w_idx = find_word(tkns, i);
	filename = NULL;
	concat_word(tkns, &w_idx, &filename);
	if (filename)
	{
		add_to_arr(&cmd->redirects_arr, "RIN");
		add_to_arr(&cmd->redirects_arr, filename);
		free(filename);
	}
	return (w_idx - i);
}

int	hndl_hdoc(t_token *tkns, t_cmd *cmd, int i, int *err)
{
	int		w_idx;
	char	*delimiter;

	if (redir_validity(tkns, i, err) == 1)
		return (0);
	w_idx = find_word(tkns, i);
	delimiter = NULL;
	concat_word(tkns, &w_idx, &delimiter);
	if (delimiter)
	{
		add_to_arr(&cmd->redirects_arr, "INSOURCE");
		add_to_arr(&cmd->redirects_arr, delimiter);
		add_to_arr(&cmd->here_doc_delim, delimiter);
		free(delimiter);
		delimiter = NULL;
	}
	return (w_idx - i);
}

int	hndl_rout(t_token *tkns, t_cmd *cmd, int i, int *err)
{
	int		w_idx;
	char	*filename;

	if (redir_validity(tkns, i, err) == 1)
		return (0);
	w_idx = find_word(tkns, i);
	filename = NULL;
	concat_word(tkns, &w_idx, &filename);
	if (filename)
	{
		add_to_arr(&cmd->redirects_arr, "ROUT");
		add_to_arr(&cmd->redirects_arr, filename);
		free(filename);
	}
	return (w_idx - i);
}

int	hndl_rout_app(t_token *tkns, t_cmd *cmd, int i, int *err)
{
	int		w_idx;
	char	*filename;

	if (redir_validity(tkns, i, err) == 1)
		return (0);
	w_idx = find_word(tkns, i);
	filename = NULL;
	concat_word(tkns, &w_idx, &filename);
	if (filename)
	{
		add_to_arr(&cmd->redirects_arr, "APPEND");
		add_to_arr(&cmd->redirects_arr, filename);
		free(filename);
	}
	return (w_idx - i);
}
