# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/21 15:04:38 by jpiquet           #+#    #+#              #
#    Updated: 2025/08/26 11:26:11 by jpiquet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -MMD -MP -I$(INCLUDE) -I$(LIBFT) -g3

INCLUDE = inc

LIBFT = Libft

GNL = Libft/gnl

PRINTF = Libft/ft_printf

MLX = minilibx-linux

VECT = vector

BIN = bin/
			
DIR_SRC = src/

SRC =	main.c \
		builtins/echo.c \
		builtins/env.c \
		builtins/export.c \
		builtins/expend.c \
		builtins/pwd.c \
		builtins/cd.c \
		builtins/unset.c \
		builtins/exit.c \
		builtins/print_export.c \
		clean/clean.c \
		clean/clean_exit.c \
		clean/free.c \
		clean/garbage_collector.c \
		clean/print_error.c \
		exec/manage_error.c	\
		exec/exec.c	\
		exec/handle_fd.c \
		exec/pipex.c \
		exec/pipex_utils.c \
		parsing/print_for_help.c \
		parsing/env_dash_i.c \
		parsing/handle_env_var.c \
		parsing/init_cmd.c \
		parsing/parsing.c \
		parsing/ft_multi_split.c \
		parsing/multi_split_utils.c \
		parsing/multi_split_utils_2.c \
		parsing/linked_list.c \
		parsing/handle_quote.c \
		parsing/identifier.c \
		parsing/identifier_2.c \
		parsing/gb_lib.c \
		parsing/syntax_error.c \
		parsing/syntax_error_2.c \
		parsing/here_doc.c \
		parsing/handle_env_var_for_here_doc.c \
		parsing/gb_split.c \
		parsing/handle_sig.c

LIBS = 	Libft/libft.a \

OBJ = $(SRC: .c=.o)
OBJ := $(addprefix $(BIN), $(SRC:.c=.o))
DEPS =   $(OBJ:.o=.d)

all: .print_header $(BIN) libs $(NAME)

libs:
	$(MAKE) -s -C Libft

$(NAME): $(OBJ) $(LIBS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS) -lreadline

# $(BIN)%.o: $(DIR_SRC)%.c | $(BIN)
# 	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)%.o: $(DIR_SRC)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN):
	mkdir -p $(BIN)

# %.o : %.c Makefile $(LIBS)
# 	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(MAKE) -s clean -C Libft
	rm -rf $(BIN) Libft/fclean

fclean: clean
	rm -f $(NAME) Libft/libft.a

re: fclean all

.print_header:
	$(call DISPLAY_TITLE)

.PHONY: all clean fclean re libs

-include $(DEPS)

########################################################################################################################
#                                                       COLORS                                                         #
########################################################################################################################

DEF_COLOR 	= \033[0;39m
GREEN		= \033[1;92m
BLUE		= \033[0;94m

########################################################################################################################
#                                                       DISPLAY                                                        #
########################################################################################################################

define DISPLAY_TITLE
						@echo "$(BLUE) __  __ _____ _   _ _____  _____ _    _ ______ _      _      "
						@echo "|  \/  |_   _| \ | |_   _|/ ____| |  | |  ____| |    | |     "
						@echo "| \  / | | | |  \| | | | | |___ | |__| | |__  | |    | |     "
						@echo "| |\/| | | | | . \` | | |  \___ \|  __  |  __| | |    | |     "
						@echo "| |  | |_| |_| |\  |_| |_ ____| | |  | | |____| |____| |____ "
						@echo "|_|  |_|_____|_| \_|_____|_____/|_|  |_|______|______|______|"
						@echo "$(GREEN)                                        by jpiquet & gaducurt$(DEF_COLOR)"
						@printf "\n"
endef
