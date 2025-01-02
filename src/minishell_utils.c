/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:14:09 by dbisko            #+#    #+#             */
/*   Updated: 2025/01/02 22:04:38 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_cmd_empty(t_cmd *cmd)
{
	if (!cmd)
		return (true);
	if (cmd->cmd_name != NULL)
		return (false);
	if (cmd->cmd_args != NULL)
		return (false);
	if (cmd->cmd_arr_w_name != NULL)
		return (false);
	if (cmd->here_doc_delim != NULL)
		return (false);
	if (cmd->success_flg != 0)
		return (false);
	if (cmd->exit != 0)
		return (false);
	if (cmd->exit_stat != 0)
		return (false);
	return (true);
}

t_program_state	*initialize_env(char **envp)
{
	t_program_state	*state;

	state = malloc(sizeof(t_program_state));
	if (state == NULL)
		return (NULL);
	(state)->env_data = NULL;
	(state)->env = allocate_arr(envp);
	(state)->env_data = init_env((state)->env);
	(state)->l_vars = NULL;
	(state)->exit_status = 0;
	(state)->exit_flag = 0;
	setup_parent_signals();
	return (state);
}

char	*get_input(int *exit_status, t_program_state *state)
{
	char	*input;
	int		exit_stat;

	input = ft_readline("minishell> ");
	if (g_interrupted == 1)
	{
		*exit_status = 130;
		g_interrupted = 0;
	}
	if (!input)
	{
		write(1, "exit\n", 5);
		exit_stat = *exit_status;
		free_program_state(state);
		state = NULL;
		exit(exit_stat);
	}
	return (input);
}

void	process_tokens(char *upd_input,
		t_program_state *state, t_cmd **cmd_list)
{
	t_token	*tokens;

	tokens = lexer(upd_input, state->env_data,
			state->l_vars, state->exit_status);
	if (tokens)
	{
		state->exit_status = parse_tokens(tokens, cmd_list,
				state->env_data, &state->l_vars);
		if (is_cmd_empty(*cmd_list))
		{
			free_cmd(*cmd_list);
			*cmd_list = NULL;
		}
		update_env_vals(&state->env_data->node, state->l_vars);
		free_lexer_data(tokens);
	}
}
