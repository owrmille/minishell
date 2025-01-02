/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:55:12 by iatopchu          #+#    #+#             */
/*   Updated: 2024/11/10 14:01:11 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

/* lexer.c */
void	store_tokens(char *input, t_token *tokens);
void	copy_token_data(t_token *src, t_token **dest, int i, int *j);
t_token	*remove_null_vals(t_token *src);
void	init_tokens_struct(t_token **tokens, int tokens_num);
t_token	*lexer(char *input, t_env *env, t_node *l_vars, int exit_status);

/* lexer_utils.c */
int		ft_isspace(char c);
char	*define_token_type(char *input, int i);
void	process_quotes(char *input, int *i, int *tokens_num);
int		are_prev_cur_fields(char *prev_type, char *cur_type);
int		find_tokens_num(char *input);

/* lexer_utils_2.c */
char	*ft_readline(char *prompt);
int		isquote(char c);
int		isquote_type(char *type);
void	init_values(char **prev_type, int *i, int *num, int *len);
int		is_new_token_type(char *prev_type, char *cur_type);

/* lexer_utils_3.c */
void	iterate_vars(char **prev, char **cur, int *len, int *i);
void	last_token(t_token **tokens, char *prev, int len, char *str);
void	update_num_len(int *num, int *len);
int		skip_symbol(char *cur_type);
int		add_extra(char *type);

/* expander.c */
void	ft_squotes(char *str, int *i, t_token *tokens, int *token_num);
int		iskey(char c);
void	ft_dquotes(char *str, int *i, t_token *tokens, int *token_num);
char	*ft_dollar(char *str, int *i);
void	expander(char *input, int *i, t_token *tokens, int *token_num);

/* dollar_expander.c */
char	*insert_var(char *s, t_info *d, int token_len);
int		char_in_str(char c, char *str, int len);
void	process_dollar_quotes(t_token *tokens, t_info *d, int i);
void	dollar_expander(t_token *tokens, t_node *env, t_node *l_var, int exit);

/* dollar_expander_utils.c */
int		find_non_key_val(char *str, int j);
char	*extract_key(char *str, int start, int end);
char	*append_val(char *key, t_info *d, char **new_str);
int		put_val(char **new_str, char *str, t_info *d, int start);
char	*append_filling(char *new_str, char *str, int end_key, int i);

/* memory_utils.c */
void	free_protect(char *ptr);
int		ft_listlen(t_token *tokens_list);
void	free_lexer_data(t_token *tokens_list);
void	free_lexer_data_2(t_token *tokens_list, int len);
char	**allocate_arr(char **envp);

/* handle_unfinished_input_utils.c */
int		has_unclosed_quotes(char *input);

/* handle_unfinished_input.c */
int		has_pipe_with_trailing_seps(char *str);
char	*process_option(char *complete_cmd, char *cutted_line, char option);
char	*concat_command(char *complete_cmd, char *line, char option);
char	*read_complete_cmd(char *complete_cmd, char option, char *prompt);
char	*handle_unfinished_input(char *input);

#endif
