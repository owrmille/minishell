NAME = minishell
INCL_DIR = ./incl
SRC_DIR = ./src
OBJ_DIR = ./obj

LIBFT_DIR = ./libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

FILES = arr_utils.c \
        arr_to_dict.c \
        executor.c \
        expander.c \
        dict_env_to_arr.c \
        dollar_expander.c \
		dollar_expander_utils.c \
        filename_utils.c \
        find_path.c \
        free_utils.c \
        ft_cd.c \
		ft_cd_utils.c \
        ft_echo.c \
        ft_env.c \
        ft_pwd.c \
		ft_export.c \
		ft_export_utils.c \
        ft_unset.c \
        ft_exit.c \
        handle_unfinished_input.c \
		handle_unfinished_input_utils.c \
        handle_redirs.c \
		handle_redirs_utils.c \
		handle_redirs_utils_2.c \
        lexer.c \
        lexer_utils.c \
		lexer_utils_2.c \
		lexer_utils_3.c \
        memory_utils.c \
        parse_token_utils.c \
		parse_token_utils_2.c \
		parse_token_utils_3.c \
        parse_utils.c \
		parse_utils_2.c \
        parser.c \
        process_external.c \
        process_builtin.c \
        local_var_utils.c \
        local_var.c \
        signals.c \
        executor_utils.c \
        executor_utils_2.c \
        executor_utils_3.c \
        executor_utils_4.c \
        minishell_utils.c

SRC = $(addprefix $(SRC_DIR)/, $(FILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))
TEST = minishell.c

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I$(INCL_DIR)
RLFLAGS = -lreadline

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS)  $(OBJ) $(TEST) $(LIBFT) $(RLFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@cd $(LIBFT_DIR) && make clean

fclean: clean
	@rm -f $(NAME)
	@cd $(LIBFT_DIR) && make fclean

re: fclean all

.PHONY: all clean fclean reNAME