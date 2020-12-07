# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/16 23:35:47 by vicmarti          #+#    #+#              #
#    Updated: 2020/12/07 13:55:43 by vicmarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS := $(shell uname)

SRC_FILES +=		main.c
SRC_FILES +=		debug.c
SRC_FILES +=		validations.c
SRC_FILES +=		math_utils.c
SRC_FILES +=		camera_list.c
SRC_FILES +=		config_reader.c
SRC_FILES +=		config_utils.c
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
LFLAGS += -L. -lft -lmlx
ifeq ($(OS), Linux)
	LFLAGS += -Xext -lX11
else
	LFLAGS += -framework OpenGL -framework AppKit
endif
AR = ar
ARFLAGS = -rc

.PHONY: all re clean fclean pft
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

$(NAME) : $(MLX) $(LIBFT) $(OBJ)
	@echo "Buildind executable."
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) -o $(NAME)
	@echo "______________________________"

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
