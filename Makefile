# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/21 15:04:38 by jpiquet           #+#    #+#              #
#    Updated: 2025/05/22 15:55:42 by gaducurt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -lreadline -Wall -Wextra -Werror 
#CFLAGS = -lreadline -Wall -Wextra -Werror

INC = inc/

SRC =	main.c				\
		parsing.c			\
		ft_multi_split.c	\

SRCDIR = src

OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
OBJDIR = obj

#LIBFT

LIBFTDIR = Libft
LIBFT_SRC = Libft/ft_atoi.c Libft/ft_bzero.c Libft/ft_calloc.c \
            Libft/ft_isalnum.c Libft/ft_isalpha.c Libft/ft_isascii.c \
            Libft/ft_isdigit.c Libft/ft_isprint.c Libft/ft_itoa.c \
            Libft/ft_memcpy.c Libft/ft_memmove.c Libft/ft_memset.c \
            Libft/ft_putchar_fd.c Libft/ft_putendl_fd.c Libft/ft_putnbr_fd.c \
            Libft/ft_putstr_fd.c Libft/ft_split.c Libft/ft_strchr.c \
            Libft/ft_strdup.c Libft/ft_strjoin.c Libft/ft_strlen.c \
            Libft/ft_strncmp.c Libft/ft_strnstr.c Libft/ft_strrchr.c \
            Libft/ft_substr.c Libft/ft_tolower.c Libft/ft_toupper.c

LIBFT_INC = Libft/libft.h

#MAKE MINISHELL

all : $(LIBFT) $(NAME)

$(NAME) : $(OBJ) $(INC)
	$(CC) $(CFLAGS) -I $(INCDIR) -o $(NAME) $(OBJ) $(LIBFT)
	@echo "$(NAME) done successfully ✅"

$(LIBFTDIR)/libft.a : $(LIBFT_SRC) $(LIBFT_INC)
	$(MAKE) -s -C $(LIBFTDIR)
	@echo "Libft done successfully ✅"

$(OBJDIR)/%.o : $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I $(INCDIR) -o $@ -c $<

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean :
	@rm -rf $(OBJDIR)
	@$(MAKE) -s -C $(LIBFTDIR) clean
	@echo "Clean done 🗑️"

fclean : clean
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFTDIR) fclean
	@echo "Full clean done 🗑️"

re: 
	@$(MAKE) -s fclean
	@$(MAKE) -s all

.PHONY : clean fclean re