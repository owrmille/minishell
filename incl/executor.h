/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:21:51 by dbisko            #+#    #+#             */
/*   Updated: 2024/11/16 13:52:38 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include <sys/stat.h>

/* arr_to_dict.c */
t_node	*create_node(char *key, char *val);
void	add_node(t_node **head, char *key, char *val);
void	split_key_value(char *str, char **key, char **val);
t_node	*arr_to_dict(char **env);

/* dict_env_to_arr.c */
int		same_str(char *str1, char *str2);
int		env_listlen(t_node *node);
int		changed_env(t_node *old, t_node *new);
void	fill_arr(t_node *env, char ***arr);
void	dict_env_to_arr(t_env *env);

/* ft_echo.c */
int		ft_arrlen(char **arr);
void	ft_echo(t_cmd *cmd);

/* ft_pwd.c */
void	ft_pwd(t_cmd *cmd);

/* ft_env.c */
void	ft_env(t_cmd *cmd);

/* ft_cd.c */
char	*get_old_path(t_cmd *cmd, char *buf);
char	*determine_new_path(t_cmd *cmd);
int		change_directory(t_cmd *cmd, char *new_path);
void	update_environment_paths(t_cmd *cmd, char *old, char *new_path);
void	ft_cd(t_cmd *cmd);

/* ft_cd_utils.c */
char	*get_val(t_node *node, char *key);
void	change_val(t_node *node, char *key, char *new_val);
int		are_too_many_arguments(t_cmd *cmd);

/* ft_unset.c */
void	remove_node(t_node **head, char *key_toremove);
void	remove_arg(t_node **node, char *arg);
void	ft_unset(t_cmd *cmd);

/* ft_export.c */
int		process_pair(char *arg, t_cmd *cmd);
int		process_key(char *arg, t_cmd *cmd);
int		has_pair(char *arg);
int		has_only_key(char *arg);
void	ft_export(t_cmd *cmd);

/* ft_export_utils.c */
int		valid_key(char *key);
int		repeated_key(t_node *node, char *key);
int		repeated_val(t_node *node, char *val);
void	find_dict_end(t_node *node, t_node **temp);
int		add_or_update_env(t_node **env, char *key, char *val, t_cmd *cmd);

/* ft_exit.c */
int		only_digits(char *str);
void	ft_exit(t_cmd *cmd);

/* handle_redirs.c */
int		process_heredoc(t_cmd *cmd, int len, int option);
int		process_in(t_cmd *cmd, char *file, int *i);
int		process_out(t_cmd *cmd, char *file, int *i);
int		process_out_append(t_cmd *cmd, char *file, int *i);
int		process_redirs(t_cmd *cmd);

/* handle_redirs_utils.c */
int		replace_heredoc_fd(t_cmd *cmd, int option, t_info *d);
int		is_pipe_handled_successfully(t_cmd *cmd, t_info *d);
void	handle_heredoc_in_child(t_cmd *cmd, t_info *d, int len);
void	handle_heredoc_in_parent(t_cmd *cmd, t_info *d, int option, int pid);

/* handle_redirs_utils_2.c */
int		does_receive_delimeter(t_cmd *cmd, int i, char *line);
void	print_heredoc_eof_message(char *delimeter);
void	write_heredoc_output(char *line, t_info *d, int len, int i);
int		read_and_write_heredoc_content(t_cmd *cmd, t_info *d, int len);
t_info	*init_info(t_cmd *cmd, int *pipe_fd);

/* process_builtin.c */
int		isbuiltin(t_cmd *cmd);
void	execute_builtin(t_cmd *cmd);
void	process_builtin(t_cmd *cmd);

/* find_path.c */
void	join_path(char **path, char *env_path, char *cmd);
int		construct_path(char **final_path, char **paths, char *cmd);
void	find_path(t_cmd *cmd, char **final_path);

/* process_external.c */
int		check_file_type(char *path);
int		is_regfile_or_dir(t_cmd *cmd, int type_num);
int		has_permissions_for_executable(t_cmd *cmd);
void	follow_path_and_execute(t_cmd *cmd, char *final_path);
void	process_external(t_cmd *cmd);

/* executor.c */
int		executor(t_cmd *cmd);

/* executor_utils.c*/

void	update_env_vals(t_node **env_node, t_node *lvars_node);
void	single_cmd_child(t_cmd *cmd);
void	single_cmd_parent(t_cmd *cmd, pid_t pid);
void	single_cmd_buildtins(t_cmd *cmd);
int		execute_single_command(t_cmd *cmd);

/* executor_utils_2.c*/
int		setup_pipe(int *fd);
void	handle_input_redirection(int prev_fd);
void	handle_output_redirection(t_cmd *temp, int *fd);
void	heredoc_in_fork(t_cmd *temp);
void	fork_and_execute(t_cmd *temp, int prev_fd, int *fd);

/* executor_utils_3.c*/
void	hndl_signal_wait_children(t_cmd *cmd);
void	wait_for_children(pid_t *child_pids, int child_count, t_cmd *cmd);
int		count_commands(t_cmd *cmd);
void	handle_parent_process(t_cmd *cmd, t_cmd *temp);
void	heredoc_in_pipes(t_cmd *temp, int prev_fd);

/* executor_utils_4.c*/
int		child_pid_malloc_check(void);

/* signals*/
void	setup_parent_signals(void);
void	setup_child_signals(void);
void	setup_ignore_signals(void);

#endif
