NAME = minishell

SRCS = main.c \
		execution.c \
		free.c \
		src/check_access.c \
		class/string/compare_string.c \
		class/string/get_string.c \
		class/string/string.c \
		class/string/string_separator.c \
		class/string/append.c \
		class/string/print.c \
		class/string/extract_string.c \
		class/string/remove.c \
		class/string/str_replace.c \
		class/redirection/redirection_type.c \
		class/redirection/fd_manager.c \
		class/redirection/redirection.c \
		class/redirection/redirect.c \
		class/redirection/detect_redirection.c \
		class/redirection/redirection_error.c \
		class/redirection/get_redirection_from_id.c \
		class/exit/exit.c \
		class/info/info.c \
		class/info/get_info.c \
		class/arg/arg.c \
		class/arg/list_to_array.c \
		builtins/builtins.c \
		builtins/env/env.c \
		builtins/env/free.c \
		builtins/env/get_env.c \
		builtins/env/print_env.c \
		builtins/env/exec_env.c \
		builtins/env/sort_env.c \
		builtins/env/env_dup.c \
		builtins/env/get_array.c \
		builtins/env/replace.c \
		builtins/env/remove.c \
		builtins/env/append.c \
		builtins/env/get_special_env.c \
		builtins/echo/exec_echo.c \
		builtins/pwd/pwd.c \
		builtins/export/exec_export.c \
		builtins/export/print_export.c \
		builtins/export/append.c \
		builtins/unset/exec_unset.c \
		builtins/cd/cd.c \
		bin/binary.c \
		class/dollars/dollars.c

OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a

CC = gcc

CFLAGS = -Wall -Wextra #-Werror

INCLUDES = -I. -lreadline

ifeq ($(UNAME), Linux)
	INCLUDES = -I. -L/usr/local/lib -I/usr/local/include -lreadline
endif

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(INCLUDES) -o $(NAME) 

$(LIBFT):
	@make -C libft

clean:
	@make clean -C libft
	rm -rf $(OBJS)

fclean: clean
	@make fclean -C libft
	rm -rf $(NAME)

re: fclean all

macos:
	git add --all
	git commit -m "Save for macos"
	git push