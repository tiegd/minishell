# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/06 11:32:07 by jpiquet           #+#    #+#              #
#    Updated: 2025/06/18 09:24:07 by jpiquet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC =		cc
CFLAGS =	-Wall -Wextra -Werror

OBJDIR =	obj
INCDIR =	libft.h \
			ft_printf/ft_printf.h \
			get_next_line/get_next_line.h

SRC =		ft_strlen.c \
			ft_strdup.c	\
			ft_isalnum.c \
			ft_memset.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memcmp.c \
			ft_memchr.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_bzero.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_calloc.c \
			ft_atoi.c \
			ft_itoa.c \
			ft_strtrim.c \
			ft_split.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c \
			ft_printf/ft_printf.c \
			ft_printf/ft_put_address.c \
			ft_printf/ft_putchar_i.c \
			ft_printf/ft_putnbr_hex.c \
			ft_printf/ft_putnbr_i.c \
			ft_printf/ft_putnbr_unsigned_i.c \
			ft_printf/ft_putstr_i.c \
			ft_printf/print_args.c \
			get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c \
			free_all.c

OBJ = $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

all : $(NAME)

$(NAME) : $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJDIR)/%.o : %.c | $(OBJDIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean :
	rm -rf $(OBJDIR)

fclean : clean
	rm -f $(NAME)

re : fclean all