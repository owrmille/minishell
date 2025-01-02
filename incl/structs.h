/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:23:33 by dbisko            #+#    #+#             */
/*   Updated: 2025/01/02 22:20:54 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_node
{
	char				*key;
	char				*val;
	struct s_node		*next;
}	t_node;

typedef struct s_env
{
	t_node	*node;
	char	**arr;
}	t_env;

// empty cmd_name means no executable
typedef struct s_cmd
{
	char			*cmd_name;
	char			**cmd_args;
	char			**cmd_arr_w_name;
	char			**here_doc_delim;
	char			**redirects_arr;
	t_env			*env;
	t_node			**lvar;
	int				success_flg;
	struct s_cmd	*next;
	int				exit;
	int				exit_stat;
	int				heredoc_fd;
	pid_t			pid;
	pid_t			*child_pids;
	int				fd[2];
	int				prev_fd;
	int				index;
}	t_cmd;

typedef struct s_token
{
	int		len;
	char	*begin;
	char	*type;
}	t_token;

typedef struct s_info
{
	t_node	*env;
	t_node	*lv;
	int		exit_status;
	int		*pipe_fd;
}	t_info;

typedef struct s_program_state
{
	int		exit_status;
	int		exit_flag;
	t_env	*env_data;
	char	**env;
	t_node	*l_vars;
}	t_program_state;

#endif