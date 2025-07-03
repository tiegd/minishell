# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/21 15:04:38 by jpiquet           #+#    #+#              #
#    Updated: 2025/07/03 10:50:39 by gaducurt         ###   ########.fr        #
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

SRC =	main.c				\
		parsing.c			\
		ft_multi_split.c	\
		linked_list.c		\
		pipex.c				\
		pipex_utils.c		\
		init_cmd.c			\
		handle_quote.c		\
		handle_fd.c			\
		clean.c				\
		clean_exit.c		\
		echo.c				\
		test_functions.c	\
		env.c				\
		export.c			\
		expend.c			\
		pwd.c				\
		cd.c				\
		unset.c 			\
		env_dash_i.c		\
		exec.c				\
			
LIBS = 	Libft/libft.a	\
SRC = 	main.c \
		echo.c \
		env.c \
		parsing.c \
		expend.c \
		ft_multi_split.c \
		linked_list.c \
		init_cmd.c \
		handle_quote.c \
		handle_env_var.c \
		multi_split_utils.c \
		multi_split_utils_2.c \
		identifier.c \
		identifier_2.c \
		free.c \
		print_for_help.c \

LIBS = 	Libft/libft.a \

OBJ = $(addprefix $(BIN), $(SRC:.c=.o))
DEPS =   $(OBJ:.o=.d)

all: .print_header $(BIN) libs $(NAME)

libs:
	$(MAKE) -s -C Libft

$(NAME): $(OBJ) $(LIBS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS) -lreadline

$(BIN)%.o: $(DIR_SRC)%.c | $(BIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN):
	mkdir -p $(BIN)

%.o : %.c Makefile $(LIBS)
	$(CC) $(CFLAGS) -o $@ -c $<

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
