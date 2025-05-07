CC = cc
CFLAGS = -Wall -Wextra -Werror

PRINTF_DIR = ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

SRCS = ft_atoi.c ft_isalnum.c ft_isdigit.c ft_memchr.c ft_memmove.c ft_putendl_fd.c \
	   ft_split.c ft_striteri.c ft_strlcpy.c ft_strncmp.c ft_strtrim.c ft_toupper.c \
	   ft_bzero.c ft_isalpha.c ft_isprint.c ft_memcmp.c ft_memset.c ft_putnbr_fd.c \
	   ft_strchr.c ft_strjoin.c ft_strlen.c ft_strnstr.c ft_substr.c ft_calloc.c \
	   ft_isascii.c ft_itoa.c ft_memcpy.c ft_putchar_fd.c ft_putstr_fd.c ft_strdup.c \
	   ft_putchar.c ft_putnbr.c ft_printerror.c \
	   ft_realloc.c ft_strcmp.c ft_strndup.c ft_matrix_dup.c ft_matrix_len.c \
	   ft_strlcat.c ft_strmapi.c ft_strrchr.c ft_tolower.c ft_lstnew_bonus.c \
	   ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
	   ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \
	   get_next_line.c ##get_next_line

OBJS = $(SRCS:.c=.o)

NAME = libft.a
RM = rm -f
AR = ar rcs

all: $(PRINTF) $(NAME)

$(PRINTF):
	@make -C $(PRINTF_DIR)

$(NAME): $(OBJS) $(PRINTF)
	@$(AR) $(NAME) $(OBJS)
	@$(AR) $(NAME) $(PRINTF)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C $(PRINTF_DIR)
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(PRINTF_DIR)

re: fclean all
