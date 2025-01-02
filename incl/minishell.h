/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:22:20 by dbisko            #+#    #+#             */
/*   Updated: 2025/01/02 22:21:06 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <limits.h>
# include <string.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../libs/libft/libft.h"

# include "structs.h"
# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "signals.h"

extern volatile int	g_interrupted;

// Atomicity: Ensures the value is read and written in one operation.
// Volatility: Ensures the compiler doesn't optimize access to the variable, 
// which could cause unexpected behavior in 
//asynchronous code like signal handlers.

/* minishell utils*/

bool			is_cmd_empty(t_cmd *cmd);
t_program_state	*initialize_env(char **envp);
char			*get_input(int *exit_status, t_program_state *state);
void			process_tokens(char *upd_input,
					t_program_state *state,
					t_cmd **cmd_list);
void			free_program_state(t_program_state *state);

#endif