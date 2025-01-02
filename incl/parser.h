/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:23:14 by dbisko            #+#    #+#             */
/*   Updated: 2024/11/12 12:23:15 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/* parser.c */
int		is_word(t_token *tkns, int index);
int		is_red(t_token *tkns, int index);
int		parse_red(t_token *tkns, t_cmd *cur_cmd, int *error_flag, int index);
void	hndl_pars_err(t_cmd *current_cmd, t_cmd **cmd_l);
int		parse_tokens(t_token *tkns, t_cmd **cmd_l, t_env *env, t_node **lvar);

/* arr_utils.c */
int		arr_len(char **arr);
char	*ft_strncat(char *dest, char *src, int n);
void	*ft_realloc(void *ptr, int old_size, int new_size);

/* filename_utils.c */
int		find_word(t_token *tokens, int index);
int		is_appdbl(t_token *tokens, int index);

/* parse_utils.c */
char	*ft_substrdup(const char *start, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
int		cnt_tkns(t_token *tokens);
int		is_key(char *env_var, char *key);
t_env	*init_env(char **l_env);

/* parse_utils_2.c */
t_cmd	*create_command_node(t_env *env_data, t_node **lvar);
char	**dup_args(char **concat_args, char **args, int arr_len);
int		set_arr_len(char **args);
char	**concat_name_args(char *name, char **args);
void	add_command(t_cmd **head, t_cmd *node);

/* parse_token_utils.c */
int		handle_arg(t_token *tkns, t_cmd *cur_cmd, int i);
int		hndl_rin(t_token *tkns, t_cmd *cmd, int i, int *err);
int		hndl_hdoc(t_token *tkns, t_cmd *cur_cmd, int i, int *err);
int		hndl_rout(t_token *tkns, t_cmd *cur_cmd, int i, int *err);
int		hndl_rout_app(t_token *tkns, t_cmd *cur_cmd, int i, int *err);

/* parse_token_utils_2.c */
int		handle_pipe(t_cmd **head, t_cmd **cmd, t_env *l_env, t_node **lvar);
int		redir_validity(t_token *tkns, int i, int *err);
int		filename_len(t_token *tkns, int i);
char	*ft_strncat_len(char *dest, const char *src, int len);
void	concat_word(t_token *tkns, int *index, char **filename);

/* parse_token_utils_3.c */
void	add_to_arr(char ***arr, char *str);
int		place_name(t_cmd *cmd, char *arg, int w_idx, int i);

/* free_utils.c */
void	free_node(t_node *node);
void	free_arr(char **arr);
void	free_list(t_node *node);
void	free_cmd(t_cmd *cmd);
void	free_env(t_env *env);

/* error_handling.c */
void	print_err(void);

/* local_var.c */
void	replace_val(t_node *list, char *key, char *val);
int		add_lvar(t_token *tkns, t_cmd *cur_cmd, int i);
void	add_node_lvar(t_cmd *cur_cmd, char *temp);

/* local_var_utils.c */
int		var_found(char *str, int len);
char	*find_val(char *str);
int		key_len(char *str);
char	*key_def(char *str);
int		key_exists(t_node *list, char *key);

#endif