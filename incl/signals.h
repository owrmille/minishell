/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:23:22 by dbisko            #+#    #+#             */
/*   Updated: 2024/11/12 12:23:23 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

void	parent_signal_handler(int sig);
void	setup_parent_signals(void);
void	setup_child_signals(void);
void	handle_eof(void);
void	setup_heredoc_signals(void);

#endif