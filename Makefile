# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/16 23:35:47 by vicmarti          #+#    #+#              #
#    Updated: 2020/11/24 09:35:58 by vicmarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SRC_FILES +=		float_print.c
#SRC_FILES +=		fmt_print.c
#SRC_FILES +=		ft_printf.c
#SRC_FILES +=		int_print.c
#SRC_FILES +=		numeric_fmt.c
#SRC_FILES +=		str_print.c
#SRC_FILES +=		symbol_fmt.c
OBJ_FILES := $(patsubst %.c, %.o, $(SRC_FILES))

SRC_DIR := sources/
OBJ_DIR := objects/

SRC :=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ :=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

LIBFT := libft.a

NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Werror -Wextra
AR = ar
ARFLAGS = -rc

.PHONY: all re bonus clean fclean pft
all : $(NAME)

libft/$(LIBFT) :
	@echo "Building libft."
	@make -C libft/ all clean
	@echo "______________________________"

$(NAME) : libft/$(LIBFT) libftprintf.h $(OBJ)
	@echo "Updating libprintf."
	@cp -v libft/$(LIBFT) $(NAME)
	@$(AR) -v $(ARFLAGS) $(NAME) $(OBJ)
	@echo "______________________________"

bonus : re

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@echo "Building object:"
	@mkdir -vp $(OBJ_DIR)
	$(CC) $(CFLAGS) $? -c -o $@
	@echo "______________________________"

pft : pft
	@git clone https://github.com/gavinfielder/pft.git pft

clean :
	@echo "Removing objects."
	@rm -rfv $(OBJ)
	@echo "______________________________"

depclean :
	@echo "Removing dependencies."
	@rm -fv $(LIBFT)
	@echo "______________________________"

fclean :
	@echo "Removing lib."
	@rm -fv $(NAME)
	@echo "______________________________"

re : fclean clean depclean all
