# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/16 23:35:47 by vicmarti          #+#    #+#              #
#    Updated: 2020/11/26 12:37:40 by vicmarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_FILES +=		main.c
SRC_FILES +=		config_reader.c
SRC_FILES +=		get_next_line.c
SRC_FILES +=		get_next_line_utils.c
OBJ_FILES := $(patsubst %.c, %.o, $(SRC_FILES))

SRC_DIR := sources/
OBJ_DIR := objects/

SRC :=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ :=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

LIBFT := libft.a
MLX := libmlx.a

NAME = miniRT

CC = cc
CFLAGS = -Wall -Werror -Wextra -I.
LFLAGS += -L. -lft -lmlx -framework OpenGL -framework AppKit
AR = ar
ARFLAGS = -rc

.PHONY: all re bonus clean fclean pft
all : $(NAME)

$(MLX) :
	@echo "Building libmlx."
	@make -C minilibx/ all 2> /dev/null
	@cp -v minilibx/$(MLX) $(MLX)
	@echo "______________________________"

$(LIBFT) :
	@echo "Building libft."
	@make -C libft/ all clean
	@cp -v libft/$(LIBFT) $(LIBFT)
	@echo "______________________________"

$(NAME) : $(MLX) $(LIBFT) minirt.h $(OBJ)
	@echo "Buildind executable."
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) -o $(NAME)
	@echo "______________________________"

bonus : re

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@echo "Building object:"
	@mkdir -vp $(OBJ_DIR)
	$(CC) $(CFLAGS) $? -c -o $@
	@echo "______________________________"

clean :
	@echo "Removing objects."
	@rm -rfv $(OBJ)
	@echo "______________________________"

depclean :
	@echo "Removing dependencies."
	@rm -fv $(LIBFT) $(MLX)
	@echo "______________________________"

fclean :
	@echo "Removing lib."
	@rm -fv $(NAME)
	@echo "______________________________"

re : fclean clean depclean all
