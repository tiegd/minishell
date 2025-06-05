# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/21 15:04:38 by jpiquet           #+#    #+#              #
#    Updated: 2025/06/04 16:08:53 by jpiquet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -g3
#CFLAGS = -lreadline -Wall -Wextra -Werror

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

INC = inc

SRCDIR = src

SRC =	$(SRCDIR)/main.c \
		$(SRCDIR)/echo.c \
		$(SRCDIR)/env.c \
		$(SRCDIR)/export.c \
		$(SRCDIR)/expend.c \
		$(SRCDIR)/pwd.c \
		$(SRCDIR)/cd.c \
		$(SRCDIR)/unset.c \
		$(SRCDIR)/env_dash_i.c \

OBJDIR = obj
OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))

LIBFT = $(LIBFTDIR)/libft.a

#MAKE MINISHELL

all : $(LIBFT) $(NAME)

$(NAME) : $(OBJ) $(INC)
	$(CC) $(CFLAGS) -I $(INC) -o $(NAME) $(OBJ) $(LIBFT)
	@echo "$(NAME) done successfully ✅"

$(LIBFTDIR)/libft.a : $(LIBFT_SRC) $(LIBFT_INC)
	$(MAKE) -s -C $(LIBFTDIR)
	@echo "Libft done successfully ✅"

$(OBJDIR)/%.o : $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I $(INC) -o $@ -c $<

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