NAME = minishell

SRCS = main.c \
		execution.c \
		free.c \
		src/check_access.c \
		src/utils.c \
		src/minishell/signal.c \
		class/string/compare_string.c \
		class/string/get_string.c \
		class/string/string.c \
		class/string/string_separator.c \
		class/string/append.c \
		class/string/print.c \
		class/string/extract_string.c \
		class/string/parser.c \
		class/string/remove.c \
		class/string/modifier/to_lower.c \
		class/string/str_replace.c \
		class/redirection/redirection_type.c \
		class/redirection/types/heredoc.c \
		class/redirection/fd_manager.c \
		class/redirection/redirection.c \
		class/redirection/create_redirection.c \
		class/redirection/redirect.c \
		class/redirection/detect_redirection.c \
		class/redirection/redirection_error.c \
		class/redirection/get_redirection_from_id.c \
		class/redirection/detect/redirection_in.c \
		class/redirection/detect/redirection_out.c \
		class/minishell/get_minishell_info.c \
		class/minishell/get_minishell.c \
		class/minishell/minishell_infos.c \
		class/minishell/minishell.c \
		class/cmd/cmd.c \
		class/cmd/init_cmd.c \
		class/cmd/cmd_utils.c \
		class/cmd/get_cmd.c \
		class/cmd/free.c \
		class/cmd/check_error.c \
		class/cmd/cmd_dup.c \
		class/file/file.c \
		class/file/clear_tmp.c \
		class/info/info.c \
		class/info/get_info.c \
		class/info/make_info.c \
		class/info/free_info.c \
		class/arg/arg.c \
		class/arg/args_dup.c \
		class/arg/free.c \
		class/arg/list_to_array.c \
		builtins/builtins.c \
		builtins/env/env.c \
		builtins/env/free.c \
		builtins/env/get_env.c \
		builtins/env/get_env_value.c \
		builtins/env/print_env.c \
		builtins/env/exec_env.c \
		builtins/env/env_dup.c \
		builtins/env/get_array.c \
		builtins/env/replace.c \
		builtins/env/remove.c \
		builtins/env/append.c \
		builtins/env/get_special_env.c \
		builtins/echo/exec_echo.c \
		builtins/exit/exec_exit.c \
		builtins/pwd/pwd.c \
		builtins/export/exec_export.c \
		builtins/export/print_export.c \
		builtins/export/append.c \
		builtins/unset/exec_unset.c \
		builtins/unset/print_error.c \
		builtins/cd/cd.c \
		builtins/cd/go_to.c \
		builtins/cd/print_error.c \
		builtins/cd/check.c \
		bin/binary.c \
		bin/binary_error.c \
		bin/get_binary.c \
		class/dollars/dollars.c \
		class/dollars/get_dollars.c

OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror
CFLAGS += -fsanitize=address

INCLUDES = -I.
COMPILATION_INCLUDES = -I$(HOME)/.brew/opt/readline/include -L$(HOME)/.brew/opt/readline/lib
DEFINE = -D TMP_PATH='"$(shell pwd)/tmp/"'

ifeq ($(UNAME), Linux)
	CFLAGS += -fsanitize=leak
	COMPILATION_INCLUDES = -L/usr/local/lib -I/usr/local/include
endif

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINE) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@rm -rf tmp
	@mkdir tmp
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(INCLUDES) $(COMPILATION_INCLUDES) -lreadline -o $(NAME) 

$(LIBFT):
	@make -C libft

clean:
	@make clean -C libft
	rm -rf $(OBJS)

fclean: clean
	@make fclean -C libft
	rm -rf $(NAME)

re: fclean all

macos: fclean
	git add --all
	git commit -m "Save for macos"
	git push

mac:
	git pull
	make all
	./minishell