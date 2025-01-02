/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:20:26 by dbisko            #+#    #+#             */
/*   Updated: 2025/01/02 22:21:35 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

volatile int	g_interrupted = 0;

void	execute_command_list(t_cmd *cmd_list, t_program_state *state)
{
	if (cmd_list)
	{
		executor(cmd_list);
		state->exit_status = cmd_list->exit_stat;
		state->exit_flag = cmd_list->exit;
		free_cmd(cmd_list);
	}
}

void	parse_and_execute(char *input, t_program_state *state)
{
	char	*upd_input;
	t_cmd	*cmd_list;

	upd_input = handle_unfinished_input(input);
	cmd_list = NULL;
	process_tokens(upd_input, state, &cmd_list);
	execute_command_list(cmd_list, state);
	free_protect(upd_input);
}

void	free_program_state(t_program_state *state)
{
	if (state == NULL)
		return ;
	if (state->env_data != NULL)
	{
		free_env(state->env_data);
		state->env_data = NULL;
	}
	if (state->l_vars != NULL)
	{
		free_list(state->l_vars);
		state->l_vars = NULL;
	}
	free(state);
	rl_clear_history();
}

void	exit_main(t_program_state *state)
{
	int	ex;

	ex = state->exit_status;
	free_program_state(state);
	state = NULL;
	exit(ex);
}

int	main(int argc, char **argv, char **envp)
{
	t_program_state	*state;
	char			*input;

	(void) argv;
	if (argc != 1)
	{
		ft_putendl_fd("minishell does not take arguments\n", 2);
		return (-1);
	}
	state = initialize_env(envp);
	if (state == NULL)
		return (-1);
	while (!state->exit_flag)
	{
		input = get_input(&state->exit_status, state);
		if (!input)
			exit_main(state);
		if (ft_strlen(input) > 0)
			parse_and_execute(input, state);
		else
			free_protect(input);
	}
	exit_main(state);
}
