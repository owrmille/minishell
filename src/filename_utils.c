/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:19:36 by dbisko            #+#    #+#             */
/*   Updated: 2025/01/02 22:05:08 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	find_word(t_token *tokens, int index)
{
	if (ft_strcmp(tokens[index + 1].type, "SEP") == 0
		&& tokens[index + 2].begin != NULL)
		return (index + 2);
	else
		return (index + 1);
}

int	is_appdbl(t_token *tokens, int index)
{
	if (ft_strcmp(tokens[index + 1].type, "FIELD") == 0
		|| ft_strcmp(tokens[index + 1].type, "EXP_FIELD") == 0
		|| ft_strcmp(tokens[index + 1].type, "WORD") == 0)
		return (1);
	else
		return (0);
}
