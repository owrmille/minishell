/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:15:46 by dbisko            #+#    #+#             */
/*   Updated: 2024/11/12 12:15:52 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_word(t_token *tkns, int index)
{
	if (ft_strcmp(tkns[index].type, "WORD") == 0
		|| ft_strcmp(tkns[index].type, "FIELD") == 0
		|| ft_strcmp(tkns[index].type, "EXP_FIELD") == 0
		|| ft_strcmp(tkns[index].type, "ENV_EXP") == 0)
		return (0);
	return (1);
}

int	is_red(t_token *tkns, int index)
{
	if (ft_strcmp(tkns[index].type, "INSOURCE") == 0)
		return (0);
	else if (ft_strcmp(tkns[index].type, "RIN") == 0)
		return (0);
	else if (ft_strcmp(tkns[index].type, "APPEND") == 0)
		return (0);
	else if (ft_strcmp(tkns[index].type, "ROUT") == 0)
		return (0);
	else
		return (1);
}

int	parse_red(t_token *tkns, t_cmd *current_cmd, int *error_flag, int index)
{
	if (ft_strcmp(tkns[index].type, "INSOURCE") == 0)
		return (hndl_hdoc(tkns, current_cmd, index, error_flag));
	else if (ft_strcmp(tkns[index].type, "RIN") == 0)
		return (hndl_rin(tkns, current_cmd, index, error_flag));
	else if (ft_strcmp(tkns[index].type, "APPEND") == 0)
		return (hndl_rout_app(tkns, current_cmd, index, error_flag));
	else if (ft_strcmp(tkns[index].type, "ROUT") == 0)
		return (hndl_rout(tkns, current_cmd, index, error_flag));
	return (1);
}

void	hndl_pars_err(t_cmd *current_cmd, t_cmd **cmd_l)
{
	free_cmd(current_cmd);
	current_cmd = NULL;
	free_cmd(*cmd_l);
	*cmd_l = NULL;
}

int	parse_tokens(t_token *tkns, t_cmd **cmd_l, t_env *env, t_node **lvar)
{
	int		index;
	int		error_flag;
	t_cmd	*current_cmd;

	index = 0;
	error_flag = 0;
	current_cmd = create_command_node(env, lvar);
	while (index < cnt_tkns(tkns) && error_flag == 0)
	{
		if (ft_strcmp(tkns[index].type, "PIPE") == 0)
			index += handle_pipe(cmd_l, &current_cmd, env, lvar);
		else if (is_word(tkns, index) == 0)
			index += handle_arg(tkns, current_cmd, index);
		else if (is_red(tkns, index) == 0)
			index += parse_red(tkns, current_cmd, &error_flag, index);
		else if (ft_strcmp(tkns[index].type, "SEP") == 0)
			index++;
	}
	if (error_flag != 0)
	{
		hndl_pars_err(current_cmd, cmd_l);
		return (error_flag);
	}
	add_command(cmd_l, current_cmd);
	return (0);
}
