SRCS += ft_atof.c
SRCS += ft_atoi.c
SRCS += ft_bzero.c
SRCS += ft_calloc.c
SRCS += ft_isalnum.c
SRCS += ft_isalpha.c
SRCS += ft_isascii.c
SRCS += ft_isdigit.c
SRCS += ft_islower.c
SRCS += ft_isprint.c
SRCS += ft_isspace.c
SRCS += ft_isupper.c
SRCS += ft_itoa.c
SRCS += ft_max.c
SRCS += ft_memccpy.c
SRCS += ft_memchr.c
SRCS += ft_memcmp.c
SRCS += ft_memcpy.c
SRCS += ft_memmove.c
SRCS += ft_memset.c
SRCS += ft_min.c
SRCS += ft_numdgts.c
SRCS += ft_numdgts_base.c
SRCS += ft_putchar_fd.c
SRCS += ft_putendl_fd.c
SRCS += ft_putnbr_base_fd.c
SRCS += ft_putnbr_fd.c
SRCS += ft_putrstr.c
SRCS += ft_putstr_fd.c
SRCS += ft_revnum.c
SRCS += ft_split.c
SRCS += ft_strchr.c
SRCS += ft_strcmp.c
SRCS += ft_strcpy.c
SRCS += ft_strdup.c
SRCS += ft_strjoin.c
SRCS += ft_strlcat.c
SRCS += ft_strlcpy.c
SRCS += ft_strlen.c
SRCS += ft_strmapi.c
SRCS += ft_strncmp.c
SRCS += ft_strndup.c
SRCS += ft_strnstr.c
SRCS += ft_strrchr.c
SRCS += ft_strtrim.c
SRCS += ft_substr.c
SRCS += ft_tolower.c
SRCS += ft_toupper.c

SRCSB += ft_lstadd_back_bonus.c
SRCSB += ft_lstadd_front_bonus.c
SRCSB += ft_lstclear_bonus.c
SRCSB += ft_lstdelone_bonus.c
SRCSB += ft_lstiter_bonus.c
SRCSB += ft_lstlast_bonus.c
SRCSB += ft_lstmap_bonus.c
SRCSB += ft_lstnew_bonus.c
SRCSB += ft_lstsize_bonus.c

OBJS = $(patsubst %.c, %.o, $(SRCS))
BONUS = $(patsubst %.c, %.o, $(SRCSB))

NAME = libft.a
CC = gcc
CFLAGS = -O3 -Wall -Werror -Wextra
AR = ar
AFLAGS = -rc

.PHONY: all re bonus clean fclean
all : $(NAME)

$(NAME) : $(OBJS)
	@$(AR) $(AFLAGS) $(NAME) $(OBJS)

bonus : $(BONUS) $(NAME) libft.h
	@$(AR) $(AFLAGS) $(NAME) $(BONUS)
#Remember: Implicit rule using CC CFLAGS CPPFLAGS
$(OBJS) : libft.h

clean :
	@rm -f $(OBJS) $(BONUS)

fclean :
	@rm -f $(NAME)

re : clean fclean all
